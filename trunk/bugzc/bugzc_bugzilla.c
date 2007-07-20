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
#include<string.h>

extern const char *_bugz_errmsg[];

/*
 *  void
    xmlrpc_client_call2f(xmlrpc_env *    const envP,
                         xmlrpc_client * const clientP,
                         const char *    const serverUrl,
                         const char *    const methodName,
                         xmlrpc_value ** const resultPP,
                         const char *    const format,
                         ...);
			 */


int bugzc_bugzilla_version(bugzc_conn *bconn, char *vbuf, size_t vsize){
	int ret;
	char *tmp_ret;
	xmlrpc_value *result;
	if(bconn->url == 0){
		bconn->err_msg = _bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return -1;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			"Bugzilla.version", &result, "()");
	if(bconn->xenv.fault_occurred){
		bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
		return -1;
	}
	else{
		if(bconn->xenv.fault_occurred){
			bconn->err_code = bconn->xenv.fault_code;
			bconn->err_msg = bconn->xenv.fault_string;
			return -1;
		}
		else{
			xmlrpc_decompose_value(&bconn->xenv, result, 
					"{s:s,*}", "version", &tmp_ret);
			if(strlen(tmp_ret) + 1 > vsize){
				//Error
				bconn->err_code = BUGZCXX_BUFFER_TOO_SMALL;
				bconn->err_msg = 
					_bugz_errmsg[BUGZCXX_BUFFER_TOO_SMALL];
				return -1;
			}
			else if(strlen(tmp_ret) + 1 <= vsize){
				strncpy(vbuf, tmp_ret, vsize);
				ret = strlen(tmp_ret);
			}
			xmlrpc_DECREF(result);
		}
	}
	return 0;
}

