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

char *fgets_s(char *str, size_t siz, FILE *fptr){
	char  *n;
	n = fgets(str, siz, fptr);
	if(strlen(n) > 2){
		while(str[strlen(str) - 1] == '\n'){
			str[strlen(str) - 1] = 0;
		}
	}
	return n;
}

int main(int argc, char *argv[]){
	char *url;
	char *login;
	char pw[24];
	char email[80];
	char fullname[80];
	char password[80];
	char version[12];
	bugzc_conn conn;
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url" \
						" and your user login after that.\n");
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
		}
		return 1;
	}
	printf("is %s\n", version);
	printf("Enter password for %s: ", login);
	fgets(pw, 23, stdin);
	if(bugzc_user_login(&conn, login, pw, 0) < 0){
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
	pw[0] = 0;
	printf("Ready to create new user account...\n");
	printf("e-mail: ");
	fgets_s(email, 79, stdin);
	printf("Full name: ");
	fgets_s(fullname, 79, stdin);
	printf("Password: ");
	fgets_s(password, 79, stdin);
	if(bugzc_user_create(&conn, email, fullname, password) < 0){
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
	printf("Account for: %s created.\n", fullname);
	bugzc_user_logout(&conn);
	return 0;
}