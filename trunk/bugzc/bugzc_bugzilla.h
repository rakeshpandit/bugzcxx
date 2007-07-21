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

#ifndef __BUGZC_BUGZILLA_H__
#define __BUGZC_BUGZILLA_H__
#include<bugzc/bugzc.h>
/** \file */

/** @brief Returns the server's installed bugzilla version.
 *  @param bconn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param vbuf A buffer where the version string is going to be stored.
 *  @param vsize The size (in bytes) of the vbuf buffer.
 *  @return The size of the string stored in the vbuf buffer or -1 if an
 *  error ocurred, you must verify the err_code and err_msg members of the
 *  bconn object for more details. */
int bugzc_bugzilla_version(bugzc_conn *bconn, char *vbuf, size_t vsize);

/** @brief Returns the timezone where the Bugzilla server is located at.
 *  Since the bugzilla server stores its time-related data according to its
 *  own location, every bug report information is bound to the timezone
 *  where the server is located at, by calling this function you can 
 *  appropiately compute dates to your local time.
 *  @param bconn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param tbuf A buffer where the timezone information is going to be
 *  	stored.
 *  @param vsize The size (in bytes) of the vbuf buffer.
 *  @return The size of the string stored in the tbuf buffer or -1 if an
 *  error ocurred, you must verify the err_code and err_msg members of the
 *  bconn object for more details. */
int bugzc_bugzilla_timezone(bugzc_conn *bconn, char *tbuf, size_t tsize);

#endif

