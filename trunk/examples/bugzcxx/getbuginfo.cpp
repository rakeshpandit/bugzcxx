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
#include<iostream>
#include<cstdio>
#include<cstring>
#include<bugzcxx/bugzcxx.h>
#include<cstdlib>
#include<sstream>
#include"utils.h"

int main(int argc, char *argv[]){
	std::string url;
	std::string login;
	std::string pass;
	unsigned int bugId = 0;
	if(argc <= 1){
		std::cerr << "You must provide bugzilla's server url (something like: https://landfill.bugzilla.org/bugzilla-3.2-branch/xmlrpc.cgi)" << std::endl;
		return 1;
	}

	try{
		for(int i = 1; i < argc; i++){
			std::string arg = argv[i];
			if(arg.compare("--login") == 0&& (++i < argc)){
				login.assign(argv[i]);
			}
			else if(arg.compare("--password") == 0 && (++i < argc)){
				pass.assign(argv[i]);
			}
			else if(arg.compare("--url") == 0 && (++i < argc)){
				url.assign(argv[i]);
			}
			else if(arg.compare("--bug-id") == 0 && (++i < argc)){
				std::stringstream s(argv[i]);
				s >> bugId;
			}
		}
		if(url.size() == 0){
			std::cerr << "You must provide bugzilla's server url (use --url parameter)." << std::endl;
			return 1;
		}
		if(login.size() == 0){
			std::cout << "Login: ";
			std::cin >> login;
		}
		if(pass.size() == 0){
			std::cout << "Password: ";
			safe_getpass(pass);
		}
		if(bugId == 0){
			std::cout << "Bug Id: ";
			std::cin >> bugId;
		}
		bugzcxx::Connection conn(url, login, pass);
		bugzcxx::BugInfo bug;
		conn.bugGet(bug, bugId);
		std::cout << bug << std::endl;
		conn.logout();
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
