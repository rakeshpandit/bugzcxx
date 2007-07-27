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

#include"config.h"
#include"bugzc_user.h"
#include"bugz_errcodes.h"

extern const char *_bugz_errmsg[];

int bugzc_user_login(bugzc_conn *bconn, const char *login, const char *pw,
		int remember){
	int id = -1;
	xmlrpc_value *result;
	if(bconn->url == 0){
		bconn->err_msg = (char*)
			_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return -1;
	}
	if(remember != 0) remember = 1;
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			"User.login", &result, "({s:s,s:s,s:b})", 
			"login", login, 
			"password", pw, 
			"remember", remember);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_INVALID_CREDENTIALS:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_CREDENTIALS];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_CREDENTIALS;
				break;
			case BUGZ_WS_ACCOUNT_DISABLED:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_ACCOUNT_DISABLED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_ACCOUNT_DISABLED;
				break;
			default:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_FAULT_OCURRED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_FAULT_OCURRED;
		}
		return -1;
	}
	else{
		xmlrpc_decompose_value(&bconn->xenv, result, 
					"{s:i,*}", "id", &id);
		xmlrpc_DECREF(result);
	}
	return id;
}

int bugzc_user_logout(bugzc_conn *conn){
	return rpc_void_call_void(conn, "User.logout");
}

