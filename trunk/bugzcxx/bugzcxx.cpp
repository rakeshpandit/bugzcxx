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
#include<bugzcxx/bugzcxx.h>
#include<bugzc/bugzc.h>
#include<string>

namespace bugzcxx {

	static const char *__curl_transport = "curl";
	static struct xmlrpc_clientparms global_xparms;

	class Connection::Info {
		public:
			bugzc_conn c;
			Info(){
				c.err_code = 0;
				c.err_msg = 0;
				c.url = 0;
				global_xparms.transport = __curl_transport;
			}
			Info(const Info &i){
				c.err_code = i.c.err_code;
				c.err_msg = i.c.err_msg;
				c.url = i.c.url;
				c.xenv.fault_occurred = i.c.xenv.fault_occurred;
				c.xenv.fault_code = i.c.xenv.fault_code;
				c.xenv.fault_string = i.c.xenv.fault_string;
			}
			void copy(const std::auto_ptr<Connection::Info> &i){
				c.err_code = i->c.err_code;
				c.err_msg = i->c.err_msg;
				c.url = i->c.url;
				c.xenv.fault_occurred = i->c.xenv.fault_occurred;
				c.xenv.fault_code = i->c.xenv.fault_code;
				c.xenv.fault_string = i->c.xenv.fault_string;
			}
			void init(const std::string &url){
				bugzc_init2(&c, url.c_str());
			}
	};

	Connection::Connection(){
		
	}
	
	Connection::Connection(const Connection &cx){
		cInfo->copy(cx.cInfo);
	}
	
	int Connection::login(const std::string &url, 
							const std::string &username,
							const std::string &password,
							int remember
							){
		int id;
		cInfo->init(url);
		if((id = bugzc_user_login(&cInfo->c, username.c_str(), 
				password.c_str(), remember)) == -1){
			if(cInfo->c.xenv.fault_occurred){
				throw XmlRPCException(cInfo->c.xenv.fault_code, 
						cInfo->c.xenv.fault_string);
			}
			else{
				throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
			}
		}
		return id;
	}
};
