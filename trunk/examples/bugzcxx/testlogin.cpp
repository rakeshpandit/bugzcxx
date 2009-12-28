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

void safe_getpass(std::string &pass){
	char  *n;
	size_t siz = 64;
	char str[siz];
	n = fgets(str, siz, stdin);
	if(strlen(n) > 2){
		while(str[strlen(str) - 1] == '\n'){
			str[strlen(str) - 1] = 0;
		}
	}
	pass = str;
}

int main(int argc, char *argv[]){
	std::string url;
	std::string login;
	std::string pass;
	try{
		for(int i = 1; i < argc; i++){
			std::string arg = argv[i];
			if(arg.compare("--login") == 0&& (++i < argc)){
				login = argv[i];
			}
			else if(arg.compare("--password") == 0 && (++i < argc)){
				pass = argv[i];
			}
			else if(arg.compare("--url") == 0 && (++i < argc)){
				url = argv[i];
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
			//safe_getpass(pass);
			std::cin >> pass;
		}
		bugzcxx::Connection conn(url, login, pass);
		std::cout << "Connected to " << url << std::endl;
		std::cout << " Version:  " << conn.version() << std::endl;
		std::cout << " Timezone: " << conn.timezone() << std::endl;
		conn.logout();
	}
	catch (bugzcxx::XmlRPCException &e) {
		std::cerr << "An XML-RPC exception was caught (" << e.code() << "): " << e.message() << std::endl;
		return 1;
	}
	return 0;
}
