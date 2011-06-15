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
	char *email;
	char version[12];
	bugzc_conn conn;
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url" \
						" and an e-mail address.\n");
		fprintf(stderr, "%s http://bugzilla.example.com johnsmith@example.com\n", argv[0]);
		return 0;
	}
	url = argv[1];
	email = argv[2];

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
		}
		return 1;
	}
	printf("is %s\n", version);
	printf("Offering an account to: %s... ", email);
	fflush(stdout);
	if(bugzc_user_offer_account_by_email(&conn, email) != 0){
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
	printf(" done\n");
	bugzc_finish(&conn);
	return 0;
}
