/*
 *  Bugzilla C/C++ XML-RPC proxy
 * 
 *  Copyright (C) Juan V. Guerrero 2007
 *  Copyright (C) Rakesh Pandit 2012
 * 
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *  Rakesh Pandit <rakesh@fedoraproject.org>
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
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include<time.h>
#include<stdio.h>

#ifndef DEFAULT_MAX_DATE_STRING_SIZE
#define DEFAULT_MAX_DATE_STRING_SIZE 100
#endif

extern const char *_bugz_errmsg[] __attribute__ ((visibility ("hidden")));
static const char *_bugz_empty_str = "";

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

static void assign_error(bugzc_conn *bconn, int err_code) {
	bconn->err_msg = (char *)_bugz_errmsg[err_code];
	bconn->err_code = err_code;
}

static void free_bugzc_obj(bugzc_conn *conn, bugzc_bug *bobj) {
	if(bobj->summary != NULL) free(bobj->summary);
	if(bobj->alias != NULL) free(bobj->alias);
	free(bobj->creation_time);
	free(bobj);
	assign_error(conn, BUGZCXX_BUGOBJ_ALLOCATION_ERROR);
}

bugzc_bug *bugzc_bug_create_obj2(bugzc_conn *conn, int id, const char *alias,
		const char *summary,
		time_t creation_tstamp,
		time_t last_change_tstamp){
	bugzc_bug *bobj = NULL;
	conn->err_code = 0;
	conn->err_msg = 0;
	struct tm tmp_tm;
	bobj = malloc(sizeof(bugzc_bug));
	bobj->summary = NULL;
	bobj->alias = NULL;
	if(bobj != NULL){
		bobj->id = id;
		if(alias == NULL)
			bobj->alias = (char *)_bugz_empty_str;
		else
			bobj->alias = strdup(alias);
		if(summary == NULL)
			bobj->summary = (char *)_bugz_empty_str;
		else
			bobj->summary = strdup(summary);
		if(bobj->summary == NULL || bobj->alias == NULL){
			free(bobj);
			assign_error(conn, BUGZCXX_BUGOBJ_ALLOCATION_ERROR);
			bobj = NULL;
			goto exit;
		}
		bobj->creation_tstamp = creation_tstamp;
		bobj->creation_time = malloc(DEFAULT_MAX_DATE_STRING_SIZE);
		localtime_r(&creation_tstamp, &tmp_tm);
		if(strftime(bobj->creation_time,
					DEFAULT_MAX_DATE_STRING_SIZE - 1, "%c", &tmp_tm) == 0) {
			free_bugzc_obj(conn, bobj);
			bobj = NULL;
			goto exit;
		}

		bobj->last_change_tstamp = last_change_tstamp;
		bobj->last_change_time = malloc(DEFAULT_MAX_DATE_STRING_SIZE);
		localtime_r(&last_change_tstamp, &tmp_tm);
		if(strftime(bobj->last_change_time,
					DEFAULT_MAX_DATE_STRING_SIZE - 1, "%c", &tmp_tm) == 0) {
			free_bugzc_obj(conn, bobj);
			bobj = NULL;
			goto exit;
		}
	} else {
		assign_error(conn, BUGZCXX_BUGOBJ_ALLOCATION_ERROR);
	}
/* OOM error handling is a bad idea. Exit as soon as one gets a
   NULL. Error handling code is never tested. This label ('exit') here
   is for old code (which does this error handling).*/
exit:
	return bobj;
}

static bugzc_bug *xmlrpc2bug(bugzc_conn *bconn, xmlrpc_value *bug_item,
						unsigned int bug_id){
	xmlrpc_value *xcreation_time = 0, *xlast_change_time = 0;
	xmlrpc_value *xsummary = 0, *xalias = 0;
	char *b_summary = 0, *b_alias = 0;
	time_t b_ctime, b_lctime;
	bugzc_bug *bug_obj = 0;
	xmlrpc_struct_find_value(&bconn->xenv, bug_item, "summary", &xsummary);
	xmlrpc_struct_find_value(&bconn->xenv, bug_item, "alias", &xalias);

	xmlrpc_struct_find_value(&bconn->xenv, bug_item,
				 "creation_time", &xcreation_time);
	xmlrpc_struct_find_value(&bconn->xenv, bug_item,
				 "last_change_time", &xlast_change_time);
	xmlrpc_read_datetime_sec(&bconn->xenv, xcreation_time, &b_ctime);
	xmlrpc_read_datetime_sec(&bconn->xenv, xlast_change_time, &b_lctime);
	xmlrpc_read_string(&bconn->xenv, xsummary, (const char **)&b_summary);
	if(xalias!=NULL && xmlrpc_value_type(xalias) == XMLRPC_TYPE_STRING)
		xmlrpc_read_string(&bconn->xenv, xalias, (const char **)&b_alias);
	else
		b_alias = (char *)_bugz_empty_str;
	bug_obj = bugzc_bug_create_obj2(bconn, bug_id, b_alias, b_summary,
			b_ctime, b_lctime);
	free(b_summary);
	if(xalias!=NULL && xmlrpc_value_type(xalias) == XMLRPC_TYPE_STRING)
		free(b_alias);
	xmlrpc_DECREF(xsummary);
	if(xalias!=NULL)
		xmlrpc_DECREF(xalias);
	xmlrpc_DECREF(xcreation_time);
	xmlrpc_DECREF(xlast_change_time);
	return bug_obj;
}

int bugzc_bug_legal_values_list(bugzc_conn *bconn, const char *field,
		const char *product_name, bugzc_list *list){
	int ret = -1;
	int r_nitems;
	int i;
	xmlrpc_value *result;
	xmlrpc_value *v_list;
	xmlrpc_value *tmp_val;
	char *tmp_item_value, *value;
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
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_FIELD_NAME);
				break;
			case BUGZ_WS_INVALID_PRODUCT:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_PRODUCT);
				break;
			case BUGZ_WS_ACCOUNT_DISABLED:
				assign_error(bconn, BUGZCXX_XMLRPC_ACCOUNT_DISABLED);
				break;
			default:
				assign_error(bconn, BUGZCXX_XMLRPC_FAULT_OCURRED);
		}
		return -1;
	} else {
		xmlrpc_decompose_value(&bconn->xenv, result, 
				"{s:A,*}", "values", &v_list);
		r_nitems = xmlrpc_array_size(&bconn->xenv, v_list);
		ret = r_nitems;
		for(i = 0; i < r_nitems; i++){
			xmlrpc_array_read_item(&bconn->xenv, v_list,
					i, &tmp_val);
			xmlrpc_decompose_value(&bconn->xenv, tmp_val, 
					"s", &tmp_item_value);
			value = strdup(tmp_item_value);
			if(value == 0){
				assign_error(bconn, BUGZCXX_LEGAL_VALUES_ARRAY_TOO_SMALL);
				ret = r_nitems * -1;
			} else {
				if(bugzc_list_append_data(list, value, strlen(value) + 1) 
						== 0x0){
					assign_error(bconn, BUGZCXX_LEGAL_VALUES_ARRAY_TOO_SMALL);
					i = r_nitems + 1;
				}
			}
			xmlrpc_DECREF(tmp_val);
		}
		xmlrpc_DECREF(result);
	}
	return ret;
}

void bugzc_bug_destroy_obj2(bugzc_bug *bug_obj){
	if(bug_obj != NULL){
		if(bug_obj->alias != NULL &&
			bug_obj->alias != _bugz_empty_str)
			free(bug_obj->alias);
		if(bug_obj->summary != NULL &&
			bug_obj->summary != _bugz_empty_str)
			free(bug_obj->summary);
		if(bug_obj->creation_time != NULL &&
			bug_obj->creation_time != _bugz_empty_str)
			free(bug_obj->creation_time);
		if(bug_obj->last_change_time != NULL &&
			bug_obj->last_change_time != _bugz_empty_str)
			free(bug_obj->last_change_time);
		free(bug_obj);
	}
}

int bugzc_bug_submit(bugzc_conn *bconn, const char *product, 
		const char *component, const char *summary,
		const char *version, const char *description,
		const char *op_sys, const char *platform,
		const char *priority, const char *severity){
	int ret = -1;
	xmlrpc_value *result;
	if(bconn->url == 0){
		assign_error(bconn, BUGZCXX_NO_INITIALIZED);
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
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_USER);
				break;
			case BUGZ_WS_INVALID_SUMMARY:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_SUMMARY);
				break;
			case BUGZ_WS_INVALID_COMPONENT:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_COMPONENT);
				break;
			case BUGZ_WS_INVALID_FIELD:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_FIELD_VALUE);
				break;
			case BUGZ_WS_INVALID_PRODUCT:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_PRODUCT);
				break;
			case BUGZ_WS_ACCOUNT_DISABLED:
				assign_error(bconn, BUGZCXX_XMLRPC_ACCOUNT_DISABLED);
				break;
			default:
				assign_error(bconn, BUGZCXX_XMLRPC_FAULT_OCURRED);
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

void bugzc_bug_destroy_list(bugzc_bug **bug_objx, size_t nelems){
	bugzc_bug *bug_obj;
	size_t i;
	bug_obj = *bug_objx;
	for(i = 0; i < nelems; i++){
		if(bug_obj[i].alias != NULL)
			free(bug_obj[i].alias);
		if(bug_obj[i].summary != NULL)
			free(bug_obj[i].summary);
		if(bug_obj[i].creation_time != NULL)
			free(bug_obj[i].creation_time);
		if(bug_obj[i].last_change_time != NULL)
			free(bug_obj[i].last_change_time);
	}
	free(bug_obj);
	*bug_objx = NULL;
}

void bugzc_bug_destroy_list2(bugzc_list *list){
	bugzc_list_free_with_data_destructor(list,
								(void *(*)(void *))bugzc_bug_destroy_obj2);
}

int bugzc_bug_get_bugs_list(bugzc_conn *bconn, unsigned int *bug_ids,
		size_t nbugid, bugzc_list *olist){
	int ret = -1;
	int i;
	xmlrpc_value *result;
	xmlrpc_value *int_array;
	xmlrpc_value *int_item;
	xmlrpc_value *bug_array;
	xmlrpc_value *bug_item;
	bugzc_bug *bug_obj;
	if(bconn->url == 0){
		assign_error(bconn, BUGZCXX_NO_INITIALIZED);
		return 0;
	}
	bugzc_list_init(olist);
	int_array = xmlrpc_array_new(&bconn->xenv);
	for(i = 0; i < (int)nbugid; i++){
		int_item = xmlrpc_build_value(&bconn->xenv, "i", bug_ids[i]);
		xmlrpc_array_append_item(&bconn->xenv, int_array, int_item);
		xmlrpc_DECREF(int_item);
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
				assign_error(bconn, BUGZCXX_XMLRPC_ACCESS_DENIED);
				break;
			case BUGZ_WS_INVALID_BUG_ID:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_BUG_ID);
				break;
			case BUGZ_WS_INVALID_BUG_ALIAS:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_BUG_ALIAS);
				break;
			case BUGZ_WS_INVALID_USER:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_USER);
				break;
			case BUGZ_WS_ACCOUNT_DISABLED:
				assign_error(bconn, BUGZCXX_XMLRPC_ACCOUNT_DISABLED);
				break;
			default:
				assign_error(bconn, BUGZCXX_XMLRPC_FAULT_OCURRED);
		}
		return -1;
	}
	else{
		xmlrpc_decompose_value(&bconn->xenv, result, 
				"{s:A,*}", "bugs", &bug_array);
		ret = xmlrpc_array_size(&bconn->xenv, bug_array);
		for(i = 0; i < ret; i++){
			xmlrpc_array_read_item(&bconn->xenv, bug_array, i, &bug_item);
			bug_obj = xmlrpc2bug(bconn, bug_item, bug_ids[i]);
			bugzc_list_append_data(olist, bug_obj, sizeof(bugzc_bug));
			xmlrpc_DECREF(bug_item);
		}
		xmlrpc_DECREF(bug_array);
	}
	xmlrpc_DECREF(result);
	return ret;
}

bugzc_bug *bugzc_bug_get_bug_info(bugzc_conn *bconn, unsigned int bug_id){
	int num_bugs;
	xmlrpc_value *result = 0;
	xmlrpc_value *int_array, *int_item;
	xmlrpc_value *bug_array = 0, *bug_item = 0;
	bugzc_bug *bug_obj = 0;
	if(bconn->url == 0){
		assign_error(bconn, BUGZCXX_NO_INITIALIZED);
		return NULL;
	}

	int_array = xmlrpc_array_new(&bconn->xenv);
	int_item = xmlrpc_build_value(&bconn->xenv, "i", bug_id);
	xmlrpc_array_append_item(&bconn->xenv, int_array, int_item);
	if(bconn->v_minor >= 4){
		xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
				"Bug.get", &result,
				"({s:A})",
				"ids", int_array
		);
	}
	else{
		xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
				"Bug.get_bugs", &result,
				"({s:A})",
				"ids", int_array
		);
	}
	xmlrpc_DECREF(int_item);
	xmlrpc_DECREF(int_array);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_ACCESS_DENIED:
				assign_error(bconn, BUGZCXX_XMLRPC_ACCESS_DENIED);
				break;
			case BUGZ_WS_INVALID_BUG_ID:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_BUG_ID);
				break;
			case BUGZ_WS_INVALID_BUG_ALIAS:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_BUG_ALIAS);
				break;
			case BUGZ_WS_INVALID_USER:
				assign_error(bconn, BUGZCXX_XMLRPC_INVALID_USER);
				break;
			case BUGZ_WS_ACCOUNT_DISABLED:
				assign_error(bconn, BUGZCXX_XMLRPC_ACCOUNT_DISABLED);
				break;
			default:
				assign_error(bconn, BUGZCXX_XMLRPC_FAULT_OCURRED);
		}
	}
	else{
		xmlrpc_decompose_value(&bconn->xenv, result,
				"{s:A,*}", "bugs", &bug_array);
		num_bugs = xmlrpc_array_size(&bconn->xenv, bug_array);
		if(num_bugs > 0){
			xmlrpc_array_read_item(&bconn->xenv, bug_array, 0, &bug_item);
			bug_obj = xmlrpc2bug(bconn, bug_item, bug_id);
			xmlrpc_DECREF(bug_item);
		}
		else{
			bug_obj = NULL;
		}
		xmlrpc_DECREF(bug_array);
	}
	xmlrpc_DECREF(result);
	return bug_obj;
}
