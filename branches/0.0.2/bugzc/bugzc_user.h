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

#ifndef __BUGZC_USER_H__
#define __BUGZC_USER_H__
#include<bugzc/bugzc.h>
/** @file 
 *  Implements all methods defined in the Bugzilla's
 *  WebService::User namespace.
 *  \todo int bugzc_user_offer_account_by_email(bugzc_conn *conn, 
 *  						const char *email);
 *  \todo int bugzc_user_create(bugz_conn *conn, const char *email, 
 * 			const char *full_name, const char *pw); */

/** @brief Logs a user into a bugzilla server.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param login a null-terminated string holding the user's username,
 *  	commonly an e-mail address
 *  @param pw a null-terminated string holding the user's account password
 *  @param remember If non-zero the login cookie will expire after the session
 *  	closes, otherwise it will outlive the user's session.
 *  @return The numeric id corresponding to the user logged in or -1 if the
 *  	login attempt failed. */
int bugzc_user_login(bugzc_conn *conn, const char *login, const char *pw,
		int remember);

/** @brief Logs out a previously logged in user.
 *  @return zero on success, non-zero on error. */
int bugzc_user_logout(bugzc_conn *conn);

#endif

