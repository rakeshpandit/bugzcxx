/*
 *  Bugzilla C/C++ XML-RPC proxy
 *
 *  Copyright (C) Juan V. Guerrero 2009
 *
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 *  This program is free software, distributed under the terms of
 *  the GNU General Public License Version 2. See the LICENSE file
 *  at the top of the source tree.
 */
#include<termios.h>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"utils.h"

void safe_getpass(std::string &pass){
	termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag = t.c_lflag & ~ECHO; //Disable terminal echo
	tcsetattr(STDOUT_FILENO, TCSANOW, &t);
	std::cin >> pass;
	t.c_lflag = t.c_lflag | ECHO; //Re-enable terminal echo
	tcsetattr(STDOUT_FILENO, TCSANOW, &t);
}
