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
 *  Bugzilla::WebService::User namespace as defined in:
 *  http://www.bugzilla.org/docs/tip/html/api/Bugzilla/WebService/User.html */

#ifdef __cplusplus
extern "C" {
#endif
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

/** @brief Sends an e-mail with an account creation offering.
 *  According to the Bugzilla API documentation this is the preferred way
 *  to create an user account. It will send an e-mail with a clickable
 *  URL where the user will input its full user name and password.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param email A null terminated string containing an e-mail where we are
 *		sending the account creation offer.
 *  @return 0 un success, non-zero otherwise */
int bugzc_user_offer_account_by_email(bugzc_conn *conn, const char *email);

/** @brief Creates an effective user account at the Bugzilla server.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param email null-terminated string with the user's e-mail address.
 *  @param fullname null-terminated string holding the user's full name.
 *  @param password null-terminated string with the user's password.
 *  @return 0 un success, non-zero otherwise */
int bugzc_user_create(bugzc_conn *conn, const char *email, const char *fullname,
						const char *password);

#ifdef __cplusplus
}
#endif
#endif
