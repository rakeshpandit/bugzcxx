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

#ifndef __BUGZC_PRODUCT_H__
#define __BUGZC_PRODUCT_H__
#include<bugzc/bugzc.h>
#include<bugzc/bugzc_list.h>
#include<bugzc/bugz_features.h>
/** @file 
 *  Implements all methods defined in the 
 *  Bugzilla::WebService::Product namespace as defined in:
 *  http://www.bugzilla.org/docs/tip/html/api/Bugzilla/WebService/Product.html
 */

#ifdef __cplusplus
extern "C" {
#endif
#ifdef USE_BUGZILLA_UNSTABLE

/** Bugzilla product structure */
typedef struct bugzc_product_s {
	/** Numeric product Id */
	int id;
	/** Product name. */
	char *name;
	/** Product description. */
	char *description;
} bugzc_product;
	
/** @brief Returns a list of product ids which the user is allowed to perform
 *  searches on.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param olist An empty bugzc_list where the resulting product ids will be
 * 		stored, call bugzc_list_free_with data when you finish using it.
 *  @return The amount of elements of the list or a negative count on failure */ 
int bugzc_product_get_selectable_products(bugzc_conn *conn, bugzc_list *olist);

/** @brief Returns a list of product ids which the user is allowed to submit
 *  bugs.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param olist An empty bugzc_list where the resulting product ids will be
 * 		stored, call bugzc_list_free_with data when you finish using it.
 *  @return The amount of elements of the list or a negative count on failure */
int bugzc_product_get_enterable_products(bugzc_conn *conn, bugzc_list *olist);

/** @brief Returns a list of product ids which the user is allowed to perform
 *  searches or enter bugs.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param olist An empty bugzc_list where the resulting product ids will be
 * 		stored, call bugzc_list_free_with data when you finish using it.
 *  @return The amount of elements of the list or a negative count on failure */
int bugzc_product_get_accessible_products(bugzc_conn *conn, bugzc_list *olist);

/** @brief Returns specific information regardig the product ids entered.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param pids An array of integers containing the product ids to query.
 *  @param npids The amount of elements contained in pids
 *  @param olist An empty bugzc_list which will return on each node the product
 *		description as elements of type bugzc_product
 *  @return The amount of elements of the list or a negative count on failure */ 
int bugzc_product_get_products(bugzc_conn *conn, int pids[], int npids, 
		bugzc_list *olist);
	
#endif
#ifdef __cplusplus
}
#endif
#endif
