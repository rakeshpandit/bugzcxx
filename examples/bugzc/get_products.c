/*
 *  Bugzilla C/C++ XML-RPC proxy
 * 
 *  Copyright (C) Juan V. Guerrero 2007
 * 
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 *  This program is free software, distributed under the terms of
 *  the GNU General Public License Version 2. See the LICENSE file
 *  at the top of the source tree.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<bugzc/bugzc.h>


#ifdef USE_BUGZILLA_UNSTABLE
	
void print_product(bugzc_product *p){
	puts("------------------------------");
	printf("ID:           %d\n", p->_id);
	printf("Name:         %s\n", p->name);
	printf("Description:  %s\n", p->description);
}

void print_product_list(bugzc_list *list){
	bugzc_node *q = 0;
	q = list->first;
	while(q != 0){
		print_product(q->d_ptr);
		q = q->next;
	}
}

void print_product_list_ids(bugzc_list *list){
	int *_id;
	bugzc_node *q = 0;
	q = list->first;
	while(q != 0){
		_id = q->d_ptr;
		if(q != list->first){
			printf(", %d", *_id);
		}
		else{
			printf("%d", *_id);
		}
		q = q->next;
	}
	if(list->count > 0){
		puts("");
	}
}

int main(int argc, char *argv[]){
	char *url;
	char *login;
	char *pass;
	char version[12];
	int *p_ids;
	int i;
	int *i_tmp;
	bugzc_list list;
	bugzc_list p_list;
	bugzc_conn conn;
	bugzc_node *node;
	if(argc <= 2){
		fprintf(stderr, "At least you must provide bugzilla's server url and login\n");
		return 0;
	}
	if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
		printf("%s --help\n%s <url> [username]\n\n", argv[0], argv[0]);
		return 0;
	}
	url = argv[1];
	login = argv[2];

	bugzc_init2(&conn, url);
	if (conn.xenv.fault_string != NULL)
	  printf("Fault (%d) %s\n",
		 conn.xenv.fault_code, conn.xenv.fault_string);

	printf("Bugzilla version at: %s ", conn.url);
	fflush(stdout);
	if(bugzc_bugzilla_version(&conn, version, 12) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
			return 1;
		}
		return 1;
	}
	printf("is %s\n", version);
	if(conn.xenv.fault_occurred){
		fprintf(stderr, "%s\n", conn.xenv.fault_string);
		return 1;
	}
	pass = getpass("Enter bugzilla password: ");
	/* Perform login */
	if(bugzc_user_login(&conn, login, pass, 0) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
			return 1;
		}
		return 1;
	}
	bugzc_list_create(&list);
	printf("Selectable product ids: ");
	if(bugzc_product_get_selectable_products(&conn, &list) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
			return 1;
		}
	}
	else{
		print_product_list_ids(&list);
		bugzc_list_free_with_data(&list);
	}
	printf("Enterable product ids: ");
	if(bugzc_product_get_enterable_products(&conn, &list) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
			return 1;
		}
	}
	else{
		print_product_list_ids(&list);
		bugzc_list_free_with_data(&list);
	}
	printf("Accessible product ids: ");
	if(bugzc_product_get_accessible_products(&conn, &list) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
			return 1;
		}
	}
	else{
		print_product_list_ids(&list);
		p_ids = (int *)malloc(list.count * sizeof(int));
		node = list.first;
		i = 0;
		while(node != 0){
			i_tmp = node->d_ptr;
			p_ids[i++] = *i_tmp;
			node = node->next;
		}
		if(bugzc_product_get_products(&conn, p_ids, list.count, &p_list) < 0){
			if(conn.err_code != 0){
				fprintf(stderr, "\n");
				if(conn.xenv.fault_occurred){
					fprintf(stderr, "%s\n", conn.xenv.fault_string);
				}
				if(conn.err_msg != 0){
					fprintf(stderr, "%s\n", conn.err_msg);
				}
				return 1;
			}	
		}
		else{
			puts("Details:");
			print_product_list(&p_list);
			bugzc_product_destroy_product_list(&p_list);
		}
		bugzc_list_free_with_data(&list);
	}
	bugzc_user_logout(&conn);
	bugzc_finish(&conn);
	return 0;
}
#else

int main(){
	puts("BugzCXX must be compiled with support for UNSTABLE interfaces"
			" before running this program");
	return 1;
}

#endif
