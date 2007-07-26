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

#ifndef __BUGZC_BUGS_H__
#define __BUGZC_BUGS_H__
#include<bugzc/bugzc.h>
/** @file 
 *  Implements all methods defined in the Bugzilla's
 *  WebService::Bug namespace. */

/** Represents a Bugzilla bug object. */
typedef struct bugzc_bug_s {
	int id;
	char *alias;
	char *summary;
	char *creation_time;
	char *last_change_time;
	time_t creation_tstamp;
	time_t last_change_tstamp;
} bugzc_bug;

/** @brief Use this function to instantiate a new bugzc_bug object.
 *  Normally you wouldn't need to call this regularly in your code also
 *  remember that each succesfull call to this function creates an in-memory
 *  object that HAS TO BE RELEASED FROM MEMORY AFTER USED for this you 
 *  must call the bugzc_bug_destroy function, DON'T FORGET IT!!!.
 *  @param id The bug's numeric id as assigned by the Bugzilla server.
 *  @param alias A null-terminated string representing alias for the bug,
 *  		aliases are assigned to bugs so normally you don't refer to
 *  		them by their bug id.
 *  @param summary A null-terminated string holding the bug summary as
 *  		entered by the reporter.
 *  @param creation_time The date and time when the bug report was entered
 *  		in the system.
 *  @param last_change_time The last day somebody perfomed a change in the
 *  		report, it could be a status change or just an issued comment
 *  @return The newly created bugzc_bug object (remember to release it
 *  bugzc_bug_destroy after use) if an error occurred while creation 0 while
 *  be returned and an error code and message will be reported trough the
 *  bugzc_conn object.
 *  @todo Compute timestamps. */
bugzc_bug *bugzc_bug_create_obj(bugzc_conn *conn, int id, const char *alias,
				const char *summary,
				const char *creation_time, 
				const char *last_change_time);
/** @brief Call this method to release a bugzc_bug object from memory.
 *  After a succesfull call to bugzc_bug_create_obj a bugzc_bug object
 *  must be released from memory by calling this function since it will
 *  properly release memory for the whole object and its members.
 *  @param bug_obj The bugzc_obj to be released from memory. */
void bugzc_bug_destroy(bugzc_bug *bug_obj);

/** @brief Returns a list of valid values related to the given Bugzilla
 *  field for a specified product.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param field The field's name.
 *  @param product_id Numeric id for the product to be researched.
 *  @param list An empty array of strings (double dimensiones char[][])
 *  	to be field with the required data, if the array permits it, after
 *  	the last element of subsequent items will be empty strings.
 *  @param nitems The maximum amount of empty slots in the \a list array
 *  	which can be used to store list items.
 *  @param max_vsize Maximum amount of permitted characters for a field
 *  	value.
 *  @return The amount of values in the list or a negative value on
 *  failure. */
int bugzc_bug_legal_values(bugzc_conn *conn, const char *field,
				const char *product_name, 
				char *list, size_t nitems,
				size_t max_vsize);

int bugzc_bug_submit(bugzc_conn *conn, const char *product, 
			const char *component, const char *summary, 
			const char *version, const char *description, 
			const char *op_sys, const char *platform, 
			const char *priority, const char *severity);
#endif

