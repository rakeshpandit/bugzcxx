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
	char pw[24];
	char version[12];
	char tzone[12];
	bugzc_conn conn;
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url\n");
		return 0;
	}
	url = argv[1];

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
		login = malloc(1024);
		printf("\nLogin (or e-mail): ");
		login[1023] = 0;
		fgets(login, 1022, stdin);
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
	printf("Server timezone: ");
	fflush(stdout);
	if(bugzc_bugzilla_timezone(&conn, tzone, 12) < 0){
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
	printf("%s\n", tzone);

	bugzc_user_logout(&conn);
	return 0;
}

