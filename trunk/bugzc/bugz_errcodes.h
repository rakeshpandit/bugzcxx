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
/** \file bugzc/bugz_errcodes.h */

enum {
	BUGZCXX_NO_INITIALIZED = 1,
	BUGZCXX_BUFFER_TOO_SMALL,
	BUGZCXX_XMLRPC_FAULT_OCURRED,
	BUGZCXX_XMLRPC_LOGIN_REQUIRED
};


#endif

