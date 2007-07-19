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

#include<bugzc/bugzc_bugzilla.h>

int bugzc_bugzilla_version(bugz_conn *bconn, char *vbuf, size_t vsize){
	int ret;
	char *tmp_ret;
	xmlrpc_value *result;
	if(bconn->url == 0){
		bconn->err_msg = "bugzc has not been initialized, initialize \
				  first.";
		bconn->err_code = -1;
		return -1;
	}
	result = xmlrpc_client_call2(&bconn->xenv, bconn->xcli, bconn->xsrv, "Bugzilla.version", "");
	if(bconn->xenv.fault_occurred){
		bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
		return -1;
	}
	else{
		xmlrpc_decompose_value(&env, result, "{s:s,*}", "id", &tmp_ret);
		if(strlen(tmp_ret) + 1 > vsize){
			//Error
			bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
			bconn->err_msg = "Destination buffer is too small, increase it, then try again";
			return -1;
		}
		esle if(strlen(tmp_ret) + 1 <= vsize){
			strncpy(vbuf, tmp_ret, vsize);
			ret = strlen(tmp_ret);
		}
		xmlrpc_DECREF(result);
	}
	return ret;
}

