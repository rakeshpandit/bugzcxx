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
#include<bugzc/bugzc_bugzilla.h>
#include<bugzc/xmlrpc_helper.h>
#include<string.h>

extern const char *_bugz_errmsg[];

int bugzc_bugzilla_version(bugzc_conn *bconn, char *vbuf, size_t vsize){
	return rpc_void_call_ret_s(bconn, "Bugzilla.version", "version", vbuf, vsize);
}

int bugzc_bugzilla_timezone(bugzc_conn *bconn, char *tbuf, size_t tsize){
	return rpc_void_call_ret_s(bconn, "Bugzilla.timezone", "timezone", tbuf, tsize);
}

