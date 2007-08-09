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
	bugzc_conn conn;

	description[0] = 0;
	if(argc <= 1){
		fprintf(stderr, "At least you must provide bugzilla's server url\n");
		return 0;
	}
	if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
		printf("%s --help\n%s <url> [username] [field_name] [product_name]\n\n");
		return 0;
	}
	url = argv[1];

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
	if(argc > 2){
		login = argv[2];
		printf("\nLogin ");
	}
	else{
		login = malloc(100);
		printf("\nLogin (or e-mail): ");
		login[99] = 0;
		fgets_s(login, 98, stdin);
	}
	printf("Password: ");
	fgets_s(pw, 23, stdin);
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
	printf("Product: ");
	fgets_s(product, 64, stdin);
	printf("Component: ");
	fgets_s(component, 64, stdin);
	printf("Short description: ");
	fgets_s(summary, 64, stdin);
	printf("Version: ");
	fgets_s(bversion, 64, stdin);
	printf("Operating System: ");
	fgets_s(op_sys, 64, stdin);
	printf("Platform: ");
	fgets_s(platform, 64, stdin);
	printf("Priority: ");
	fgets_s(priority, 64, stdin);
	printf("Severity: ");
	fgets_s(severity, 64, stdin);
	printf("Enter bug description below, when finished just type a single dot '.'\n");
	do{
		fgets_s(tmp, 127, stdin);
		if(strcmp(tmp, ".\n") == 0 || strlen(tmp) < 4){
			break;
		}
		else{
			strcat(description, tmp);
		}
	}while(strcmp(tmp, ".") != 0);
	printf("\nSubmitting bug... ");
	fflush(stdout);

	
	bug_id = bugzc_bug_submit(&conn, product, component, summary, bversion,
				description, op_sys, platform, priority, severity);

	if(bug_id >= 0){
		printf("done, bug id #%d\n", bug_id);
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


