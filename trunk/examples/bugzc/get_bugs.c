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
	int i;

	char product[65];
	char component[65];
	char summary[256];
	char bversion[65];
	char description[2048];
	char op_sys[65];
	char platform[65];
	char priority[65];
	char severity[65];
	char tmp[128];
	int bug_id;
	int qi;
	size_t n;
	bugzc_conn conn;
	bugzc_bug *l = 0;

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
	/* Build bug array list */
	for(i = 3; i < argc; i++){
		sscanf(argv[i], "%d", &qi);
		printf("Querying info for #%d...\n", qi);
		l = bugzc_bug_get_bugs(&conn, &qi, 1, &n);
		if(l != 0){
			printf("Bug id:\t\t%d\nSummary:\t%s\n", l[0].id, l[0].summary);
			printf("Created On:\t%s (%lu)\n", l[0].creation_time,
					l[0].creation_tstamp);
			printf("Last Change On:\t%s (%lu)\n\n", l[0].last_change_time,
					l[0].last_change_tstamp);
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
	}
	bugzc_user_logout(&conn);
	return 0;
}


