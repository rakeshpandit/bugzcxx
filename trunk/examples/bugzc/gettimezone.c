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
#include<bugzc/bugzc.h>


int main(int argc, char *argv[]){
	char *url;
	char time_zone[36];

	bugzc_conn conn;
	url = argv[1];
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url\n");
		fprintf(stderr, "%s http://bugzilla.example.com\n", argv[0]);
		return 0;
	}

	bugzc_init2(&conn, url);
	printf("Bugzilla timezone at: %s ", conn.url);
	fflush(stdout);
	if(conn.xenv.fault_occurred){
		fprintf(stderr, "%s\n", conn.xenv.fault_string);
		return 1;
	}
	if(bugzc_bugzilla_timezone(&conn, time_zone, 36) < 0){
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
	printf("is %s\n", time_zone);

	return 0;
}

