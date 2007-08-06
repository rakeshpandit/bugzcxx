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
#include<bugzc/bugzc.h>


int main(int argc, char *argv[]){
	char *url;
	char *login;
	char *field_name;
	char *product_name;
	char pw[24];
	char version[12];
	char list[100][100];
	int nlist;
	size_t max_vsize;
	int i;
	bugzc_conn conn;
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url\n");
		return 0;
	}
	if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
		printf("%s --help\n%s <url> [username] [field_name] [product_name]\n\n");
		return 0;
	}
	url = argv[1];
	nlist = 100;
	max_vsize = 100;

	bugzc_init(&conn, url, strlen(url));
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
	if(argc > 2){
		login = argv[2];
		printf("\nLogin ");
	}
	else{
		login = malloc(100);
		printf("\nLogin (or e-mail): ");
		login[99] = 0;
		fgets(login, 98, stdin);
	}
	printf("Password: ");
	fgets(pw, 23, stdin);
	/* Perform login */
	if(bugzc_user_login(&conn, login, pw, 0) < 0){
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
	pw[0] = 0;
	if(argc > 3){
		field_name = argv[3];
		if(argc > 4) printf("\n");
	}
	else{
		field_name = malloc(60);
		printf("\nField name: ");
		field_name[59] = 0;
		fgets(field_name, 58, stdin);
	}
	if(argc > 4){
		product_name = argv[4];
	}
	else{
		product_name = malloc(60);
		printf("\nProduct name: ");
		product_name[59] = 0;
		fgets(product_name, 58, stdin);
	}
	if((nlist = bugzc_bug_legal_values(&conn, field_name, product_name, (char *)list, nlist, max_vsize)) < 0){
		if(conn.err_code != 0){
			fprintf(stderr, "\n");
			if(conn.xenv.fault_occurred){
				fprintf(stderr, "%s\n", conn.xenv.fault_string);
			}
			if(conn.err_msg != 0){
				fprintf(stderr, "%s\n", conn.err_msg);
			}
		}
		return 1;
	}
	printf("Legal %s values are: ", field_name);
	for(i = 0; i < nlist; i++){
		if(i > 0) printf(", ");
		printf("%s", list[i]);
	}
	printf("\n");
	bugzc_user_logout(&conn);
	return 0;
}


