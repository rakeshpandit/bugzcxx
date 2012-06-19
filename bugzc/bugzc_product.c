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
#include"bugzc.h"
#include"bugz_errcodes.h"
#include"bugzc_product.h"
#include"xmlrpc_helper.h"
#include<string.h>
#include<stdlib.h>

extern const char *_bugz_errmsg[];

#ifdef USE_BUGZILLA_UNSTABLE


static bugzc_product *__create_product(int _id, const char *_name, 
									const char *_desc){
	bugzc_product *p = 0;
	p = malloc(sizeof(bugzc_product));
	if(p != 0x0){
		p->_id = _id;
		p->name = strdup(_name);
		p->description = strdup(_desc);
		if(p->name == 0 || p->description == 0){
			if(p->name) free(p->name);
			if(p->description) free(p->description);
			free(p);
			p = 0;
		}
	}
	return p;
}

int bugzc_product_get_selectable_products(bugzc_conn *conn, bugzc_list *olist){
	bugzc_list_create(olist);
	return rpc_void_call_ret_list_int(conn, "Product.get_selectable_products",
						"ids", olist);
}

int bugzc_product_get_enterable_products(bugzc_conn *conn, bugzc_list *olist){
	bugzc_list_create(olist);
	return rpc_void_call_ret_list_int(conn, "Product.get_enterable_products",
							"ids", olist);
}

int bugzc_product_get_accessible_products(bugzc_conn *conn, bugzc_list *olist){
	bugzc_list_create(olist);
	return rpc_void_call_ret_list_int(conn, "Product.get_accessible_products",
								"ids", olist);
}

static const char *pp[] = { 
		"id",
		"name",
		"description"
};

int bugzc_product_get_products(bugzc_conn *bconn, int pids[], int npids, 
		bugzc_list *olist){
	
	int ret = -1;
	xmlrpc_value *result = 0;
	xmlrpc_value *arr;
	xmlrpc_value *tmp_val;
	xmlrpc_value *int_array;
	xmlrpc_value *int_item;
	int  i, _id;
	char *_name, *_description;
	bugzc_product *tmp_product;
	bugzc_list_create(olist);
	int_array = xmlrpc_array_new(&bconn->xenv);
	for(i = 0; i < npids; i++){
		int_item = xmlrpc_build_value(&bconn->xenv, "i", pids[i]);
		xmlrpc_array_append_item(&bconn->xenv, int_array, int_item);
	}
	xmlrpc_client_call2f(&bconn->xenv, bconn->xcli, bconn->url,
					"Product.get_products", &result,
					"({s:A})", 
					"ids", int_array
		);
	xmlrpc_DECREF(int_array);
	if(bconn->xenv.fault_occurred){
		switch(bconn->xenv.fault_code){
			case BUGZ_WS_AUTH_REQUIRED:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_LOGIN_REQUIRED];
				bconn->err_code = BUGZCXX_XMLRPC_LOGIN_REQUIRED;
				break;
			default:
				bconn->err_msg = (char *)
					_bugz_errmsg[BUGZCXX_XMLRPC_FAULT_OCURRED];
				bconn->err_code = BUGZCXX_XMLRPC_FAULT_OCURRED;
		}
		return -1;
	} else {
		xmlrpc_decompose_value(&bconn->xenv, result, 
				"{s:A,*}", "products", &arr);
		ret = xmlrpc_array_size(&bconn->xenv, arr);
		for(i = 0; i < ret; i++){
				xmlrpc_array_read_item(&bconn->xenv, arr,
							i, &tmp_val);
				xmlrpc_decompose_value(&bconn->xenv, tmp_val, 
							"{s:i,s:s,s:s,*}",
							pp[0], &_id,
							pp[1], &_name,
							pp[2], &_description);
				if(bconn->xenv.fault_occurred){
					bconn->err_msg = (char *)
						_bugz_errmsg[BUGZCXX_XMLRPC_FAULT_OCURRED];
					bconn->err_code = BUGZCXX_XMLRPC_FAULT_OCURRED;
					bugzc_product_destroy_product_list(olist);
					ret = -1;
					break;
				}
				tmp_product = __create_product(_id, _name, _description);
				if(tmp_product == 0){
					bconn->err_msg = (char *)
								_bugz_errmsg[BUGZCXX_PRODUCTOBJ_ALLOCATION_FAILED];
					bconn->err_code = BUGZCXX_PRODUCTOBJ_ALLOCATION_FAILED;
					bugzc_product_destroy_product_list(olist);
					ret = -1;
					break;
				} else {
					bugzc_list_append_data(olist, tmp_product, 
											sizeof(bugzc_product));
				}
		}
		xmlrpc_DECREF(result);
	}
	return ret;
}

void bugzc_product_destroy_obj(bugzc_product *p){
	if(p->name)
		free(p->name);
	if(p->description)
		free(p->description);
	free(p);
}

void bugzc_product_destroy_product_list(bugzc_list *list){
	bugzc_list_free_with_data_destructor(list, (void *(*)(void *))bugzc_product_destroy_obj);
}
#endif
