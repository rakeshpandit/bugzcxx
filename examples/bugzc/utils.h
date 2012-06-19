/*
 *  Bugzilla C/C++ XML-RPC proxy
 *
 *  Copyright (C) Juan V. Guerrero 2010
 *
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 *  This program is free software, distributed under the terms of
 *  the GNU General Public License Version 2. See the LICENSE file
 *  at the top of the source tree.
 */

#ifndef __UTILS_H__
#define __UTILS_H__
#include<stdio.h>

extern char *fgets_s(char *str, size_t siz, FILE *fptr);
extern char *safe_getpass(const char *prompt);

#endif
