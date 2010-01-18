/*
 *  Bugzilla C/C++ XML-RPC proxy
 *
 *  Copyright (C) Juan V. Guerrero 2010
 *
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 *  This program is free software, distributed under the terms of
 *  the GNU General Public License Version 2. See the LICENSE file
 *  at the top of the source tree.
 */
#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"

#ifndef DEFAULT_GETPASS_MAX_CHARS
#define DEFAULT_GETPASS_MAX_CHARS 32
#endif

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

char *safe_getpass(const char *prompt){
	static char pass[DEFAULT_GETPASS_MAX_CHARS];
	printf("%s", prompt);
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag = t.c_lflag & ~ECHO; //Disable terminal echo
	tcsetattr(0, TCSANOW, &t);
	fgets_s(pass, DEFAULT_GETPASS_MAX_CHARS - 1, stdin);
	t.c_lflag = t.c_lflag | ECHO; //Re-enable terminal echo
	tcsetattr(0, TCSANOW, &t);
	return pass;
}
