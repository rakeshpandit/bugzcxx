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
#include"bugzc_bug.h";
#include"bugz_errcodes.h"

extern const char *_bugz_errmsg[];

int bugzc_bug_legal_values(bugzc_conn *bconn, const char *field,
				const char *product_name,
				char *list, size_t nitems,
				size_t max_vsize)
{
	int ret = -1;
	int r_nitems;
	int i;
	xmlrpc_value *result;
	xmlrpc_value *v_list;
	xmlrpc_value *tmp_val;
	char *tmp_item_value;
	if(bconn->url == 0){
		bconn->err_msg = (char *)_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return -1;
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
			"Bug.legal_values", &result, "({s:s,s:s})", 
			"field", field, 
			"product_id", product_name);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_INVALID_FIELD_NAME:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_FIELD_NAME];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_FIELD_NAME;
				break;
			case BUGZ_WS_INVALID_PRODUCT:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_PRODUCT];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_PRODUCT;
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
					"{s:A,*}", "values", &v_list);
		r_nitems = xmlrpc_array_size(&bconn->xenv, v_list);
		//xmlrpc_decompose_value(&bconn->xenv, result, 
		//			"{s:i,*}", "id", &id);
		if(r_nitems > nitems){
			/* We got a problem, array list is to small to store all
			 * values, report it back and set error status. */
			bconn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_LEGAL_VALUES_ARRAY_TOO_SMALL];
			bconn->err_code = 
				BUGZCXX_LEGAL_VALUES_ARRAY_TOO_SMALL;
			ret = r_nitems * -1;
		}
		else{
			ret = r_nitems;
			for(i = 0; i < r_nitems; i++){
				xmlrpc_array_read_item(&bconn->xenv, v_list,
							i, &tmp_val);
				xmlrpc_decompose_value(&bconn->xenv, tmp_val, 
							"s", &tmp_item_value);
				if(strlen(tmp_item_value) > max_vsize + 1){
					ret = -1 * (strlen(tmp_item_value)
							+ 1);
					bconn->err_msg = (char *)
						_bugz_errmsg[BUGZCXX_LEGAL_VALUES_ITEM_SIZE_TOO_SMALL];
					bconn->err_code = 
						BUGZCXX_LEGAL_VALUES_ITEM_SIZE_TOO_SMALL;
					break;
				}
				else{
					strcpy(list + i * max_vsize, tmp_item_value);
				}
				xmlrpc_DECREF(tmp_val);
			}
		}
		xmlrpc_DECREF(result);
	}
	return ret;
}

