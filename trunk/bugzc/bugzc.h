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

#ifndef __BUGZC_H__
#define __BUGZC_H__
#include<bugzc/bugzc_version.h>
#include<xmlrpc-c/base.h>
#include<xmlrpc-c/client.h>

typedef struct bugz_conn_s {
	char *url;
	int err_code;
	char *err_msg;
	xmlrpc_env xenv;
	xmlrpc_client *xcli;
	xmlrpc_server_info *xsrv;
} bugzc_conn;

/****************************************************************************
 * Initializes bugzilla connection establishing its location url.
 * A call to this function will not perform any connection related
 * tests and will only initialize internal variables.
 * @param bc A bugz_conn connection element to be initialized.
 * @param url A null terminated string containing Bugzilla's URL, something
 * 	like: http://bugzilla.example.com/xmlrpc.cgi
 * @param surl The amount of characters in url.
 * @return 0 on success, any other value on failure.
 ***************************************************************************/
int bugzc_init(bugz_conn *bc, const char *url, size_t surl);

#include<bugzc/bugzilla.h>
#endif

