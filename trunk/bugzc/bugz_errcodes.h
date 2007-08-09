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
/** @file */

#ifdef __cplusplus
extern "C" {
#endif
enum BUGZCXX_INTERNAL_ERRCODES {
	BUGZCXX_NO_INITIALIZED = 1,
	BUGZCXX_BUFFER_TOO_SMALL,
	BUGZCXX_XMLRPC_FAULT_OCURRED,
	BUGZCXX_XMLRPC_LOGIN_REQUIRED,
	BUGZCXX_XMLRPC_INVALID_CREDENTIALS,
	BUGZCXX_XMLRPC_ACCOUNT_DISABLED,
	BUGZCXX_XMLRPC_INVALID_BUG_ALIAS,
	BUGZCXX_XMLRPC_INVALID_BUG_ID,
	BUGZCXX_XMLRPC_ACCESS_DENIED,
	BUGZCXX_XMLRPC_INVALID_PRODUCT, 
	BUGZCXX_XMLRPC_INVALID_FIELD_NAME,
	BUGZCXX_LEGAL_VALUES_ARRAY_TOO_SMALL,
	BUGZCXX_LEGAL_VALUES_ITEM_SIZE_TOO_SMALL,
	BUGZCXX_BUGOBJ_ALLOCATION_ERROR,
	BUGZCXX_XMLRPC_INVALID_FIELD_VALUE,
	BUGZCXX_XMLRPC_INVALID_COMPONENT,
	BUGZCXX_XMLRPC_INVALID_SUMMARY,
	BUGZCXX_XMLRPC_INVALID_USER,
	BUGZCXX_XMLRPC_ACCT_ILLEGAL_EMAIL,
	BUGZCXX_XMLRPC_ACCT_ALREADY_EXISTS,
	BUGZCXX_XMLRPC_ACCT_PW_TOO_SHORT,
	BUGZCXX_XMLRPC_ACCT_PW_TOO_LONG,
};

enum BUGZILLA_WEBSERVICE_ERRCODES {
	BUGZ_WS_INVALID_BUG_ALIAS = 100,
	BUGZ_WS_INVALID_BUG_ID = 101,
	BUGZ_WS_ACCESS_DENIED = 102,
	BUGZ_WS_INVALID_ALIAS = 103,
	BUGZ_WS_INVALID_FIELD = 104,
	BUGZ_WS_INVALID_COMPONENT = 105,
	BUGZ_WS_INVALID_PRODUCT = 106,
	BUGZ_WS_INVALID_SUMMARY = 107,
	BUGZ_WS_INVALID_FIELD_NAME = 108,
	BUGZ_WS_INVALID_CREDENTIALS = 300,
	BUGZ_WS_ACCOUNT_DISABLED = 301,
	BUGZ_WS_AUTH_REQUIRED = 410,
	BUGZ_WS_ILLEGAL_EMAIL = 500,
	BUGZ_WS_ACCT_ALREADY_EXISTS = 501,
	BUGZ_WS_PW_TOO_SHORT = 502,
	BUGZ_WS_PW_TOO_LONG = 503,
	BUGZ_WS_INVALID_USER = 504
};

#ifdef __cplusplus
}
#endif
#endif

