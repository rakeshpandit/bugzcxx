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
#include<stdlib.h>
#ifdef RESPONSE_TIME_DEBUGGING
#include<sys/time.h>
#include<stdio.h>
#endif

extern const char *_bugz_errmsg[];

xmlrpc_value *rpc_void_call(bugzc_conn *bconn, const char *mname){
	xmlrpc_value *result;
#ifdef RESPONSE_TIME_DEBUGGING
	struct timeval t1, t2, tr;
	gettimeofday(&t1, 0);
#endif
	if(bconn->url == 0){
		bconn->err_msg = (char *)_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return 0;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			mname, &result, "()");
#ifdef RESPONSE_TIME_DEBUGGING
	gettimeofday(&t2, 0);
	timersub(&t2, &t1, &tr);
	fprintf(stderr, "Call to method %s took: %d ms\n", mname, (int)(tr.tv_usec / 1000));
#endif
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
	const char *tmp_ret = 0;
        xmlrpc_value *tmp_xmlrpc = 0;
	xmlrpc_value *result = 0;

	result = rpc_void_call(bconn, mname);
	if(result == 0){
		return -1;
	} else {
		xmlrpc_struct_find_value(&bconn->xenv, result, 
				vname, &tmp_xmlrpc);
                xmlrpc_read_string(&bconn->xenv, tmp_xmlrpc, &tmp_ret);
		if(strlen(tmp_ret) + 1 > sbuf){
			//Error
			bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
			bconn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUFFER_TOO_SMALL];
		} else if(strlen(tmp_ret) + 1 <= sbuf){
			strncpy(buf, tmp_ret, sbuf);
			ret = strlen(tmp_ret);
		}
		xmlrpc_DECREF(result);
		if(tmp_ret != 0) free((void *)tmp_ret);
	}
	return ret;
}

int rpc_void_call_void(bugzc_conn *bconn, const char *mname){
	xmlrpc_value *result = rpc_void_call(bconn, mname);
        if(result == 0)
                return -1;
        xmlrpc_DECREF(result);
	return 0;
}

int rpc_s_call_void(bugzc_conn *bconn, const char *mname,
		const char *param,
		const char *s){
	int ret = 0;	
	xmlrpc_value *result = 0;
#ifdef RESPONSE_TIME_DEBUGGING
	struct timeval t1, t2, tr;
	gettimeofday(&t1, 0);
#endif
	if(bconn->url == 0){		
		bconn->err_msg = (char *)_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return -1;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
				mname, &result, "({s:s})",
				param, s
				);
#ifdef RESPONSE_TIME_DEBUGGING
	gettimeofday(&t2, 0);
	timersub(&t2, &t1, &tr);
	fprintf(stderr, "Call to method %s took: %d ms\n", mname, (int)(tr.tv_usec / 1000));
#endif
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
	if(result == 0){
		ret = -1;
	} else {
		xmlrpc_DECREF(result);
		
	}
	return ret;
}

int rpc_void_call_ret_list_int(bugzc_conn *bconn, const char *mname,
		const char *vname, bugzc_list *list){
	int ret = -1;
	xmlrpc_value *result = 0;
	xmlrpc_value *arr;
	xmlrpc_value *tmp_val;
	int val, i;
	int *val_s;

	result = rpc_void_call(bconn, mname);
	if(result == 0){
		return -1;
	} else {
		xmlrpc_struct_find_value(&bconn->xenv, result, 
				vname, &arr);
		ret = xmlrpc_array_size(&bconn->xenv, arr);
		for(i = 0; i < ret; i++){
				xmlrpc_array_read_item(&bconn->xenv, arr,
							i, &tmp_val);
				xmlrpc_decompose_value(&bconn->xenv, tmp_val, 
							"i", &val);
				val_s = malloc(sizeof(int));
				if(val_s){
					val_s[0] = val;
					bugzc_list_append_data(list, (void *)val_s, sizeof(int));
				} else {
					ret *= -1;
					break;
				}
		}
		xmlrpc_DECREF(result);
	}
	return ret;	
}
