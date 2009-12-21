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

void print_bug_obj(bugzc_bug *l){
	printf("Bug id:\t\t%d\nSummary:\t%s\n", l->id, l->summary);
	printf("Created On:\t%s (%lu)\n", l->creation_time,
			l->creation_tstamp);
	printf("Last Change On:\t%s (%lu)\n\n", l->last_change_time,
			l->last_change_tstamp);
}

void print_bug_list(bugzc_list *list){
	bugzc_node *q;
	q = list->first;
	while(q != 0){
		print_bug_obj((bugzc_bug *)q->d_ptr);
		q = q->next;
	}
}

int main(int argc, char *argv[]){
	char *url;
	char *login;
	char *pass;
	char version[12];
	int i;

	char description[2048];
	unsigned int *qi;
	bugzc_conn conn;
	bugzc_list list;

	description[0] = 0;
	if(argc < 4 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
		printf("%s --help\n%s <url> <username> <bugid>...\n\n", argv[0], argv[0]);
		return 0;
	}
	url = argv[1];
	login = argv[2];

	bugzc_init2(&conn, url);
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

	qi = (unsigned int *)malloc((argc - 3) * sizeof(int));

	/* Build bug array list */
	for(i = 3; i < argc; i++){
		sscanf(argv[i], "%d", &qi[i - 3]);
		printf("Querying info for #%d...\n", qi[i - 3]);
	}
	if(bugzc_bug_get_bugs_list(&conn, qi, argc - 3, &list) >= 0){
		print_bug_list(&list);
		bugzc_bug_destroy_list2(&list);
	}
	else{
		fprintf(stderr, "\n");
		if(conn.xenv.fault_occurred){
			fprintf(stderr, "%s\n", conn.xenv.fault_string);
		}
		if(conn.err_msg != 0){
			fprintf(stderr, "%s\n", conn.err_msg);
		}
		return 1;
	}
	bugzc_user_logout(&conn);
	return 0;
}


