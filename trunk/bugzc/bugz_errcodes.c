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
	"Success",
	"bugzcxx has not been properly initialized",
	"Given buffer is too small in size",
	"An XML-RPC failure has been detected look at the"
	".xenv.fault_code or .xenv.fault_string members of"
	"the connection object for more information",
	"Required operation requires user authentication, "
	"please login first",
	"Given username or password is not valid",
	"Account is currently disabled",
	"Specified bug alias is invalid",
	"Given bug ID is not valid",
	"Access Denied, verify your account privileges",
	"Given product name or ID are not valid or doesn't exists at all,"
		" while submitting bugs for special product also verify"
		" that you are allowed to actually submit bugs to it.",
	"Given Bugzilla product field is not valid",
	"Given array to store legal values is too small, returning minimum"
		" required array size as a negative number",
	"Per item size is too small for at least one element on the list,"
		" returning minimum required amount of characters for the"
		" biggest entry as a negative number",
	"Unable to allocate a bugzc_bug object, not enough memory",
	"A field value is not correct, verify with get_legal_values",
	"Given component is invalid or does not exists",
	"Specified summary is not correct, is it empty?",
	"Either the QA Contact, Assignee, or CC lists have some invalid user in them"
};

