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
#include"bugz_errcodes.h"

const char *_bugz_errmsg[] = {
	"Success",
	"Library (bugzcxx) has not been properly initialized",
	"Given buffer is too small in size",
	"An XML-RPC failure has been detected, look at the"
	".xenv.fault_code or .xenv.fault_string members of"
	"the connection object for more information",
	"Required operation requires user authentication, "
	"please login first",
	"Given username or password is not valid",
	"Account is currently disabled",
	"Specified bug alias is invalid",
	"Given bug ID is not valid",
	"Access Denied, verify your account privileges",
	"Either given product name/ID are not valid (doesn't exists at all) or"
		" you don't have permissions to submit bugs for product in process",
	"Given Bugzilla product field is not valid",
	"Given array to store legal values is too small, returning minimum"
		" required array size as a negative number",
	"Per item size is too small for at least one element on the list,"
		" returning minimum required amount of characters for the"
		" biggest entry as a negative number",
	"Unable to allocate a bugzc_bug object, not enough memory",
	"A field value is not correct (verify with get_legal_values)",
	"Given component is invalid (does not exists)",
	"Specified summary is not correct (is it empty?)",
	"Invalid user in QA Contact or Assignee or CC lists",
	"Invalid email adress",
	"Unable to create account, username already exists",
	"Given password is too short",
	"Given password is too long",
	"Unable to allocate an instance of bugzc_product"
};
