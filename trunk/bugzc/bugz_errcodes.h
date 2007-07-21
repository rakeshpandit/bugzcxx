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

#ifndef __BUGZC_ERRCODES_H__
#define __BUGZC_ERRCODES_H__
#include<bugzc/bugzc.h>
/** \file */

enum {
	BUGZCXX_NO_INITIALIZED = 1,
	BUGZCXX_BUFFER_TOO_SMALL,
	BUGZCXX_XMLRPC_FAULT_OCURRED,
	BUGZCXX_XMLRPC_LOGIN_REQUIRED,
	BUGZCXX_XMLRPC_INVALID_CREDENTIALS,
	BUGZCXX_XMLRPC_ACCOUNT_DISABLED
};

enum bugzilla_webservice_errcodes {
	BUGZ_WS_INVALID_CREDENTIALS = 300,
	BUGZ_WS_ACCOUNT_DISABLED = 301,
	BUGZ_WS_AUTH_REQUIRED = 410,
	BUGZ_WS_ILLEGAL_EMAIL = 500,
	BUGZ_WS_ACCT_ALREADY_EXISTS = 501,
	BUGZ_WS_PW_TOO_SHORT = 502,
	BUGZ_WS_PW_TOO_LONG = 503
};


#endif

