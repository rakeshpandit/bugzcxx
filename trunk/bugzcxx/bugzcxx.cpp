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

#ifndef DEFAULT_MINIMUM_VERSION_STRING_LENGTH
#define DEFAULT_MINIMUM_VERSION_STRING_LENGTH 16
#endif

#ifndef DEFAULT_MINIMUM_TZ_STRING_LENGTH
#define DEFAULT_MINIMUM_TZ_STRING_LENGTH 96
#endif

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

	Connection::Connection() : cInfo(new Connection::Info){
		sess_id = -1;
	}
	
	Connection::Connection(const std::string &url) :
			cInfo(new Connection::Info){
		sess_id = -1;
		cInfo->init(url);
	}

	Connection::Connection(const std::string &url,
			const std::string &username,
			const std::string &password
			) : cInfo(new Connection::Info){
		sess_id = login(url, username,password);
	}

	Connection::Connection(const Connection &cx) :
			cInfo(new Connection::Info){
		cInfo->copy(cx.cInfo);
	}
	
	Connection::~Connection(){
		bugzc_finish(&cInfo->c);
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

	std::string Connection::version(){
		char buf[DEFAULT_MINIMUM_VERSION_STRING_LENGTH];
		if(bugzc_bugzilla_version(&cInfo->c, buf, DEFAULT_MINIMUM_VERSION_STRING_LENGTH) == -1){
			if(cInfo->c.xenv.fault_occurred){
				throw XmlRPCException(cInfo->c.xenv.fault_code,
						cInfo->c.xenv.fault_string);
			}
			else{
				throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
			}
		}
		return std::string(buf);
	}

	void Connection::logout(){
		if(bugzc_user_logout(&cInfo->c) != 0){
			if(cInfo->c.xenv.fault_occurred){
				throw XmlRPCException(cInfo->c.xenv.fault_code,
						cInfo->c.xenv.fault_string);
			}
			else{
				throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
			}
		}
	}

	std::string Connection::timezone(){
		char buf[DEFAULT_MINIMUM_TZ_STRING_LENGTH];
		if(bugzc_bugzilla_timezone(&cInfo->c, buf, DEFAULT_MINIMUM_TZ_STRING_LENGTH) == -1){
			if(cInfo->c.xenv.fault_occurred){
				throw XmlRPCException(cInfo->c.xenv.fault_code,
						cInfo->c.xenv.fault_string);
			}
			else{
				throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
			}
		}
		return std::string(buf);
	}

	void Connection::accountOfferTo(const std::string &email_address){
		bugzc_user_offer_account_by_email(&cInfo->c, email_address.c_str());
		if(cInfo->c.xenv.fault_occurred){
			throw XmlRPCException(cInfo->c.xenv.fault_code,
					cInfo->c.xenv.fault_string);
		}
		else if(cInfo->c.err_code != 0){
			throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
		}
	}

	int Connection::accountCreate(const std::string &email, const std::string &fullname,
			const std::string &password){
		int user_id = -1;
		if((user_id = bugzc_user_create(&cInfo->c, email.c_str(), fullname.c_str(),
				password.c_str())) != 0){
			if(cInfo->c.xenv.fault_occurred){
				throw XmlRPCException(cInfo->c.xenv.fault_code,
						cInfo->c.xenv.fault_string);
			}
			else{
				throw Exception(cInfo->c.err_code, cInfo->c.err_msg);
			}
		}
		return user_id;
	}
};
