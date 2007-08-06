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
#include"xmlrpc_helper.h"
#include"bugz_errcodes.h"
#include<string.h>

extern const char *_bugz_errmsg[];

xmlrpc_value *rpc_void_call(bugzc_conn *bconn, const char *mname){
	xmlrpc_value *result;
	if(bconn->url == 0){
		bconn->err_msg = (char *)_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return 0;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			mname, &result, "()");
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_AUTH_REQUIRED:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_LOGIN_REQUIRED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_LOGIN_REQUIRED;
				break;
			default:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_FAULT_OCURRED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_FAULT_OCURRED;
		}
		return 0;
	}
	return result;
}

int rpc_void_call_ret_s(bugzc_conn *bconn, const char *mname, 
				const char *vname, 
				char *buf, size_t sbuf){
	int ret = -1;
	char *tmp_ret;
	xmlrpc_value *result = 0;

	result = rpc_void_call(bconn, mname);
	if(result == 0){
		return -1;
	}
	else{
		xmlrpc_decompose_value(&bconn->xenv, result, 
				"{s:s,*}", vname, &tmp_ret);
		if(strlen(tmp_ret) + 1 > sbuf){
			//Error
			bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
			bconn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUFFER_TOO_SMALL];
		}
		else if(strlen(tmp_ret) + 1 <= sbuf){
			strncpy(buf, tmp_ret, sbuf);
			ret = strlen(tmp_ret);
		}
		xmlrpc_DECREF(result);
	}
	return ret;
}

int rpc_void_call_void(bugzc_conn *bconn, const char *mname){
	xmlrpc_value *result;
	if(bconn->url == 0){
		bconn->err_msg = _bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return -1;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			mname, &result, "()");
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_AUTH_REQUIRED:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_LOGIN_REQUIRED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_LOGIN_REQUIRED;
				break;
			default:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_FAULT_OCURRED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_FAULT_OCURRED;
		}
		return bconn->xenv.fault_code;
	}
	xmlrpc_DECREF(result);
	return 0;
}