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

const char *_bugz_errmsg[] = {
	"",
	"bugzcxx has not been properly initialized",
	"Given buffer is too small in size",
	"An XML-RPC failure has been detected look at the"
	".xenv.fault_code or .xenv.fault_string members of"
	"the connection object for more information",
	"Required operation requires user authentication, "
	"please login first",
	"Given username or password is not valid",
	"Account is currently disabled"
};

