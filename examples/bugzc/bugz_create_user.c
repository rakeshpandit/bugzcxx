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
#include"utils.h"

int main(int argc, char *argv[]){
	char *url;
	char *login;
	char *pass;
	char email[80];
	char fullname[80];
	char password[80];
	char version[12];
	bugzc_conn conn;
	if(argc <= 2){
		fprintf(stderr, "At least you must provide bugzilla's server url" \
						" and your user login after that.\n");
		fprintf(stderr, "%s http://bugzilla.example.com johnsmith@example.com\n", argv[0]);
		return 0;
	}
	url = argv[1];
	login = argv[2];

	bugzc_init2(&conn, url);
	if (conn.xenv.fault_string != NULL)
	  printf("Fault (%d) %s\n",
		 conn.xenv.fault_code, conn.xenv.fault_string);

	printf("Bugzilla version at: %s ", conn.url);
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
	fflush(stdout);
	pass = safe_getpass("Enter bugzilla password: ");
	if(bugzc_user_login(&conn, login, pass, 0) < 0){
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
	bugzc_finish(&conn);
	return 0;
}
