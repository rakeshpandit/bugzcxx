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
	char version[12];
	url = argv[1];

	bugzc_conn conn;

	bugzc_init(&conn, url, strlen(url));
	printf("Bugzilla version at: %s ", conn.url);
	fflush(stdout);
	if(conn.xenv.fault_occurred){
		fprintf(stderr, "%s\n", conn.xenv.fault_string);
		return 1;
	}
	if(bugzc_bugzilla_version(&conn, version, 12) != 0){
		fprintf(stderr, "%s\n", conn.xenv.fault_string);
		return 1;
	}
	printf("is %s\n", version);



	return 0;
}

