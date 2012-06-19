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
#include<bugzc/bugz_features.h>
#include<bugzc/bugz_errcodes.h>
#include<xmlrpc-c/base.h>
#include<xmlrpc-c/client.h>
/** \file bugzc.h */

#ifdef __cplusplus
extern "C" {
#endif
typedef struct bugz_conn_s {
	char *url;
	int err_code;
	char *err_msg;
	xmlrpc_env xenv;
	xmlrpc_client *xcli;
	int v_major;
	int v_minor;
	int v_patch;
} bugzc_conn;

/** @brief Initializes bugzilla connection establishing its location url.
 *  A call to this function will not perform any connection related
 *  tests and will only initialize internal variables.
 *  @param bc A bugz_conn connection element to be initialized.
 *  @param url A null terminated string containing Bugzilla's URL, something
 * 	like: http://bugzilla.example.com/xmlrpc.cgi
 *  @return 0 on success, any other value on failure.
 ***************************************************************************/
int bugzc_init2(bugzc_conn *bc, const char *url);

/** @brief Destroys all data related to a bugzilla session, it must be called
 *  after you've completed all your work so all related data is released from
 *  memory.
 *  @param bc The bugz_conn connection element to be disposed of. */
void bugzc_finish(bugzc_conn *bc);
#ifdef __cplusplus
}
#endif

#include<bugzc/bugzc_bugzilla.h>
#include<bugzc/bugzc_user.h>
#include<bugzc/bugzc_bug.h>
#ifdef USE_BUGZILLA_UNSTABLE
#include<bugzc/bugzc_product.h>
#endif
#endif

