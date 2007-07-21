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

#ifndef __BUGZCXX_XML_RPC_HELPER_H__
#define __BUGZCXX_XML_RPC_HELPER_H__
#include<bugzc/bugzc.h>
#include<xmlrpc-c/base.h>
#include<xmlrpc-c/client.h>
/** @file */

/** @internal 
 *
 */
xmlrpc_value *rpc_void_call(bugzc_conn *bconn, const char *mname);

/** @internal 
 *
 */
int rpc_void_call_ret_s(bugzc_conn *bconn, const char *mname, 
				const char *vname, 
				char *buf, size_t sbuf);
/** @internal 
 * @brief Eases calling an xml-rpc method which has no
 * arguments and returns nothing.
 * @return Returns non-zero if the operation failed
 */
int rpc_void_call_void(bugzc_conn *bconn, const char *mname);
#endif

