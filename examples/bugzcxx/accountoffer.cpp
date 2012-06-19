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
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bugzcxx/bugzcxx.h>
#include<cstdlib>
#include"utils.h"

int main(int argc, char *argv[]){
	if(argc <= 2){
		std::cerr << "You must provide bugzilla's server url (something like: https://landfill.bugzilla.org/bugzilla-3.2-branch/xmlrpc.cgi)" << std::endl;
		std::cerr << "Don't forget to provide the user email as well, call this program like this: " << std::endl;
		std::cerr << " " << argv[0] << " <bugzilla-url> <user-email>" << std::endl;
		return 1;
	}
	try{
		bugzcxx::Connection conn(argv[1]);
		conn.accountOfferTo(argv[2]);
	}
	catch (bugzcxx::XmlRPCException &e) {
		std::cerr << "An XML-RPC exception was caught (" << e.code() << "): " << e.message() << std::endl;
		return 1;
	}
	catch (bugzcxx::Exception &e1){
		std::cerr << e1.message() << std::endl;
		return 1;
	}
	return 0;
}
