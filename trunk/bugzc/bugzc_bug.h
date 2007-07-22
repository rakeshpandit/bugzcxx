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

#ifndef __BUGZC_BUGS_H__
#define __BUGZC_BUGS_H__
#include<bugzc/bugzc.h>
/** @file 
 *  Implements all methods defined in the Bugzilla's
 *  WebService::Bug namespace. */

/** @brief Returns a list of valid values related to the given Bugzilla
 *  field for a specified product.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param field The field's name.
 *  @param product_id Numeric id for the product to be researched.
 *  @param list An empty array of strings (double dimensiones char[][])
 *  	to be field with the required data, if the array permits it, after
 *  	the last element of subsequent items will be empty strings.
 *  @param nitems The maximum amount of empty slots in the \a list array
 *  	which can be used to store list items.
 *  @param max_vsize Maximum amount of permitted characters for a field
 *  	value.
 *  @return The amount of values in the list or a negative value on
 *  failure. */
int bugzc_bug_legal_values(bugzc_conn *conn, const char *field,
				const char *product_name, 
				char *list, size_t nitems,
				size_t max_vsize);

#endif

