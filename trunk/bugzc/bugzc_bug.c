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
#include"bugzc_bug.h"
#include"bugz_errcodes.h"
#include<string.h>
#include<stdlib.h>

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

bugzc_bug *bugzc_bug_create_obj(bugzc_conn *conn, int id, const char *alias,
				const char *summary,
				const char *creation_time, 
				const char *last_change_time){
	bugzc_bug *bobj = 0;
	conn->err_code = 0;
	conn->err_msg = 0;
	bobj = malloc(sizeof(bugzc_bug));
	if(bobj != NULL){
		bobj->id = id;
		if(alias == NULL){
			bobj->alias = strdup("");
		}
		else{
			bobj->alias = strdup(alias);
		}
		if(bobj->alias == NULL){
			free(bobj);
			conn->err_code = BUGZCXX_BUGOBJ_ALLOCATION_ERROR;
			conn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUGOBJ_ALLOCATION_ERROR];
			bobj = 0;
		}
		if(summary == NULL){
			bobj->summary = strdup("");
		}
		else{
			bobj->summary = strdup(summary);
		}
		if(bobj->summary == NULL){
			free(bobj);
			conn->err_code = BUGZCXX_BUGOBJ_ALLOCATION_ERROR;
			conn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUGOBJ_ALLOCATION_ERROR];
			bobj = 0;
		}
		if(creation_time == NULL){
			bobj->creation_time = strdup("");
		}
		else{
			bobj->creation_time = strdup(creation_time);
		}
		if(bobj->creation_time == NULL){
			free(bobj);
			conn->err_code = BUGZCXX_BUGOBJ_ALLOCATION_ERROR;
			conn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUGOBJ_ALLOCATION_ERROR];
			bobj = 0;
		}
		if(last_change_time == NULL){
			bobj->last_change_time = strdup("");
		}
		else{
			bobj->last_change_time = strdup(last_change_time);
		}
		if(bobj->last_change_time == NULL){
			free(bobj);
			conn->err_code = BUGZCXX_BUGOBJ_ALLOCATION_ERROR;
			conn->err_msg = (char *)
				_bugz_errmsg[BUGZCXX_BUGOBJ_ALLOCATION_ERROR];
			bobj = 0;
		}
		if(bobj != 0){
			/* Compute timestamps */
		}
	}
	else{
		conn->err_code = BUGZCXX_BUGOBJ_ALLOCATION_ERROR;
		conn->err_msg = (char *)
			_bugz_errmsg[BUGZCXX_BUGOBJ_ALLOCATION_ERROR];
	}
	return bobj;
}

void bugzc_bug_destroy_obj(bugzc_bug **bug_objx){
	bugzc_bug *bug_obj;
	bug_obj = *bug_objx;
	if(bug_obj != NULL){
		if(bug_obj->alias != NULL) free(bug_obj->alias);
		if(bug_obj->summary != NULL) free(bug_obj->summary);
		if(bug_obj->creation_time != NULL) free(bug_obj->creation_time);
		if(bug_obj->last_change_time != NULL) free(bug_obj->last_change_time);
		free(bug_obj);
		*bug_objx = NULL;
	}
}


static const char *bp[] = {
	"product",
	"component",
	"summary",
	"version",
	"description",
	"op_sys",
	"platform",
	"priority",
	"severity"
};
int bugzc_bug_submit(bugzc_conn *bconn, const char *product, 
			const char *component, const char *summary, 
			const char *version, const char *description, 
			const char *op_sys, const char *platform, 
			const char *priority, const char *severity){
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
					"Bug.create", &result,
					"({s:s,s:s,s:s,s:s,s:s,s:s,s:s,s:s,s:s})", 
					bp[0], product,
					bp[1], component,
					bp[2], summary,
					bp[3], version,
					bp[4], description,
					bp[5], op_sys,
					bp[6], platform,
					bp[7], priority,
					bp[8], severity
		);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_INVALID_USER:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_USER];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_USER;
				break;
			case BUGZ_WS_INVALID_SUMMARY:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_SUMMARY];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_SUMMARY;
				break;
			case BUGZ_WS_INVALID_COMPONENT:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_COMPONENT];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_COMPONENT;
				break;
			case BUGZ_WS_INVALID_FIELD:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_FIELD_VALUE];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_FIELD_VALUE;
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
					"{s:i,*}", "id", &ret);
		xmlrpc_DECREF(result);
	}
	return ret;
}

void bigzc_bug_destroy_list(bugzc_bug **bug_objx, size_t nelems){
	bugzc_bug *bug_obj;
	size_t i;
	bug_obj = *bug_objx;
	for(i = 0; i < nelems; i++){
		if(bug_obj[i].alias != NULL) free(bug_obj[i].alias);
		if(bug_obj[i].summary != NULL) free(bug_obj[i].summary);
		if(bug_obj[i].creation_time != NULL) free(bug_obj[i].creation_time);
		if(bug_obj[i].last_change_time != NULL) free(bug_obj[i].last_change_time);
	}
	free(bug_obj);
	*bug_objx = NULL;
}


bugzc_bug *bugzc_bug_get_bugs(bugzc_conn *bconn, unsigned int *bug_ids,
				size_t nbugid, size_t *rbugid){
	bugzc_bug *ret = 0;
	int r_nitems;
	int i;
	xmlrpc_value *result;
	xmlrpc_value *v_list;
	xmlrpc_value *tmp_val;
	xmlrpc_value *int_array;
	xmlrpc_value *int_item;
	xmlrpc_value *bug_array;
	xmlrpc_value *bug_item;
	xmlrpc_value *ctime;
	xmlrpc_value *lctime;
	char *b_summary;
	char *b_alias;
	char *tmp_str;
	char *b_ctime;
	char *b_lctime;
	if(bconn->url == 0){
		bconn->err_msg = (char *)_bugz_errmsg[BUGZCXX_NO_INITIALIZED];
		bconn->err_code = BUGZCXX_NO_INITIALIZED;
		return 0;
	}
	int_array = xmlrpc_array_new(&bconn->xenv);
	for(i = 0; i < nbugid; i++){
		int_item = xmlrpc_build_value(&bconn->xenv, "i", bug_ids[i]);
		xmlrpc_array_append_item(&bconn->xenv, int_array, int_item);
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
					"Bug.get_bugs", &result,
					"({s:A})", 
					"ids", int_array
		);
	xmlrpc_DECREF(int_array);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_ACCESS_DENIED:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_ACCESS_DENIED];
				bconn->err_code = 
					BUGZCXX_XMLRPC_ACCESS_DENIED;
				break;
			case BUGZ_WS_INVALID_BUG_ID:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_BUG_ID];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_BUG_ID;
				break;
			case BUGZ_WS_INVALID_BUG_ALIAS:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_BUG_ALIAS];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_BUG_ALIAS;
				break;
			case BUGZ_WS_INVALID_USER:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_INVALID_USER];
				bconn->err_code = 
					BUGZCXX_XMLRPC_INVALID_USER;
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
		return 0;
	}
	else{
		xmlrpc_decompose_value(&bconn->xenv, result, 
					"{s:A,*}", "bugs", &bug_array);
		*rbugid = xmlrpc_array_size(&bconn->xenv, bug_array);
		ret = malloc(sizeof(bugzc_bug) * *rbugid);
		for(i = 0; i < *rbugid; i++){
			xmlrpc_array_read_item(&bconn->xenv, bug_array, i, &bug_item);
#ifdef USE_BUGZILLA_UNSTABLE
#error Not implemented yet
#else
			xmlrpc_decompose_value(&bconn->xenv, bug_item, 
						"{s:s,s:i,s:s,s:8,s:8,*}",
						"summary", &b_summary,
						"id", &ret[i].id,
						"alias", &b_alias,
						"creation_time", 
						&b_ctime,
						"last_change_time", 
						&b_lctime
					);
			ret[i].creation_time = strdup(b_ctime);
			ret[i].last_change_time = strdup(b_lctime);
#endif
			ret[i].summary = strdup(b_summary);
			if(b_alias == 0){
				ret[i].alias = malloc(1 * sizeof(char));
				ret[i].alias[0] = 0;
			}
			else{
				ret[i].alias = strdup(b_alias);
			}
		}
		xmlrpc_DECREF(result);
	}
	return ret;

}

