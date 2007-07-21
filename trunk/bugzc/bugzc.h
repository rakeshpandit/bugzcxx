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
#include<bugzc/bugz_errcodes.h>
#include<xmlrpc-c/base.h>
#include<xmlrpc-c/client.h>
/** \file bugzc.h */

typedef struct bugz_conn_s {
	char *url;
	int err_code;
	char *err_msg;
	xmlrpc_env xenv;
	xmlrpc_client *xcli;
} bugzc_conn;

/** @brief Initializes bugzilla connection establishing its location url.
 *  A call to this function will not perform any connection related
 *  tests and will only initialize internal variables.
 *  @param bc A bugz_conn connection element to be initialized.
 *  @param url A null terminated string containing Bugzilla's URL, something
 * 	like: http://bugzilla.example.com/xmlrpc.cgi
 *  @param surl The amount of characters in url.
 *  @return 0 on success, any other value on failure.
 *  @todo Perform url validation
 ***************************************************************************/
int bugzc_init(bugzc_conn *bc, const char *url, size_t surl);

#include<bugzc/bugzc_bugzilla.h>
#include<bugzc/bugzc_user.h>
#endif

