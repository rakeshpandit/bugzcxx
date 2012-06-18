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
#include<bugzc/bugzc_list.h>
/** @file 
 *  Implements all methods defined in the Bugzilla's
 *  Bugzilla::WebService::Bug namespace as defined in:
 *  http://www.bugzilla.org/docs/tip/html/api/Bugzilla/WebService/Bug.html */

#ifdef __cplusplus
extern "C" {
#endif

/** Represents a Bugzilla bug object. */
typedef struct bugzc_bug_s {
	/** The bug numeric id */
	int id;
	/** Bug alias description if the remote Bugzilla installation is
	 *  configured for bug alias handling */
	char *alias;
	/** Short description as entered by the reporter */
	char *summary;
	/** Bug creation time in ISO 8601 format as a null terminated
	 *  string formatted using the preferred locale's notation */
	char *creation_time;
	/** Last date when the bug information was changed. It is a 
	 *  null-terminated string formatted using the preferred locale's
	 *  notation */
	char *last_change_time;
	/** Bug creation date/time as a unix timestamp */
	time_t creation_tstamp;
	/** Bug last modification date/time as a unix timestamp */
	time_t last_change_tstamp;
	/** @internal An opaque pointer which holds more information regarding the
	 *  bug, it is intended for internal use only. */
	void *info;
	/** @internal Holds the size of the info buffer or zero if its holding no data */
	size_t info_size;
} bugzc_bug;

/** @brief Use this function to instantiate a new bugzc_bug object.
 *  Normally you wouldn't need to call this regularly in your code also
 *  remember that each successful call to this function creates an in-memory
 *  object that HAS TO BE RELEASED FROM MEMORY AFTER USED for this you 
 *  must call the bugzc_bug_destroy function, DON'T FORGET IT!!!.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
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
 *  @return The newly created bugzc_bug object.  In case of an error 0 will
 *  be returned and an error code along with a message through bugzc_conn
 *  object. */
bugzc_bug *bugzc_bug_create_obj(bugzc_conn *conn, int id, const char *alias,
				const char *summary,
				const char *creation_time, 
				const char *last_change_time)
				__attribute__ ((__deprecated__));

/** @brief Use this function to instantiate a new bugzc_bug object.
 *  Normally you wouldn't need to call this regularly in your code also
 *  remember that each successful call to this function creates an in-memory
 *  object that HAS TO BE RELEASED FROM MEMORY AFTER USED for this you
 *  must call the bugzc_bug_destroy function, DON'T FORGET IT!!!.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param id The bug's numeric id as assigned by the Bugzilla server.
 *  @param alias A null-terminated string representing alias for the bug,
 *  		aliases are assigned to bugs so normally you don't refer to
 *  		them by their bug id.
 *  @param summary A null-terminated string holding the bug summary as
 *  		entered by the reporter.
 *  @param creation_tstamp A time_t timestamp that represent the point in
 *  		time when the bug was entered in the system.
 *  @param last_change_tstamp The last day somebody perfomed a change in the
 *  		report, it could be a status change or just an issued comment
 *  @return The newly created bugzc_bug object.  In case of an error 0 will
 *  be returned and an error code along with a message through bugzc_conn
 *  object. */
bugzc_bug *bugzc_bug_create_obj2(bugzc_conn *conn, int id, const char *alias,
				const char *summary,
				time_t creation_tstamp,
				time_t last_change_tstamp);

/** @brief Call this method to release a bugzc_bug object from memory.
 *  After a succesfull call to bugzc_bug_create_obj a bugzc_bug object
 *  must be released from memory by calling this function since it will
 *  properly release memory for the whole object and its members.
 *  @param bug_obj The bugzc_obj to be released from memory. 
 *  @deprecated Please use bugzc_bug_destroy_obj2, as of BugzCXX 0.1.0 this
 *  function will be eliminated.*/
void bugzc_bug_destroy_obj(bugzc_bug **bug_obj)
				__attribute__ ((__deprecated__));
/** @brief Call this method to release a bugzc_bug object from memory.
 *  After a succesfull call to bugzc_bug_create_obj a bugzc_bug object
 *  must be released from memory by calling this function since it will
 *  properly release memory for the whole object and its members.
 *  The main difference with this function and bugzc_bug_destroy_obj is that 
 *  the latter requires a double pointer and at the end will change the pointer
 *  address to 0x0, this function does not perform that last step. 
 *  @param bug_obj The bugzc_obj to be released from memory.  */
void bugzc_bug_destroy_obj2(bugzc_bug *bug_obj);

/** @brief Releases a dynamically allocated array of bugz_bug objects from
 *  memory.
 *  Most commonly you'll be using this function to release memory from an
 *  array alocated from functions like bugzc_bug_get_bugs.
 *  @param bug_obj A reference to a preivouls allocated dynamic array of
 *  	bug_obj elements.
 *  @param nelems The amount of elements contained in the array. */
void bugzc_bug_destroy_list(bugzc_bug **bug_obj, size_t nelems);

/** @brief Releases memory used in a bugzc_list which containg bugzc_bug objects
 *  @param list The bugzc_list which is about to the freed. */
void bugzc_bug_destroy_list2(bugzc_list *list);

/** @brief Returns a list of valid values related to the given Bugzilla
 *  field for a specified product.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param field The field's name.
 *  @param product_name null-terminated string representing the product to
 * 		be researched.
 *  @param list An empty array of strings (double dimensiones char[][])
 *  	to be field with the required data, if the array permits it, after
 *  	the last element of subsequent items will be empty strings.
 *  @param nitems The maximum amount of empty slots in the \a list array
 *  	which can be used to store list items.
 *  @param max_vsize Maximum amount of permitted characters for a field
 *  	value.
 *  @return The amount of values in the list or a negative value on
 *  failure. 
 *  @deprecated This function will be no more when we reach 0.1.0, use
 *  bugzc_bug_legal_values_list instead. */
int bugzc_bug_legal_values(bugzc_conn *conn, const char *field,
				const char *product_name, 
				char *list, size_t nitems,
				size_t max_vsize)
				__attribute__ ((__deprecated__));
/** @brief Returns a list of valid values related to the given Bugzilla
 *  field for a specified product.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param field The field's name.
 *  @param product_name null-terminated string representing the product to
 * 		be researched.
 *  @param list An empty bugzc_list linked list that will store the data values
 *  @return The amount of values in the list or a negative value on
 *  failure. */
int bugzc_bug_legal_values_list(bugzc_conn *conn, const char *field,
				const char *product_name, bugzc_list *list);

/** @brief Use this function to submit new bug information to a bugzilla
 *  server installation.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param product A null terminated string representing the name of 
 *  	the product with problems as defined in the Bugzilla server
 *  	installation.
 *  @param component A null terminated string specifying the product 
 *  	component with problems.
 *  @param summary A null terminated string with a short description of
 *  	the software bug.
 *  @param version A null terminated string specifying the product/component
 *  	software version that is presenting the problem.
 *  @param description A null terminated string with a full and detailed 
 *  	description of the software problem.
 *  @param op_sys A null terminated string representing the operating 
 *  	system where the problem has been observed.
 *  @param platform A null terminated string containing the platform where
 *  	the bug was first detected.
 *  @param priority A null terminated string containing the bug resolution
 *  	priority.
 *  @param severity A null terminated string containing the bug's severity
 *  	level.
 *  @return An integer with the bug number as assigned by the remote Bugzilla
 *  	installation. If an error ocurred during bug submission this function
 *  	will return a value smaller than 0, to check the reason verify the
 *  	err_code and err_msg members of the connection object. */
int bugzc_bug_submit(bugzc_conn *conn, const char *product, 
			const char *component, const char *summary, 
			const char *version, const char *description, 
			const char *op_sys, const char *platform, 
			const char *priority, const char *severity);

/** @brief Gives detailed information about a bugid or an array of bug ids.
 *  @deprecated Instead use bugzc_bug_get_bugs_list as of BugzCXX 0.1.0 the
 *  function bugzc_bug_get_bugs will be eliminated.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param bug_ids An array of numeric bug ids to query from the Bugzilla
 *  	remote installation server.
 *  @param nbugid The amount of elements contained in the bug_ids array.
 *  @param rbugid Will return the amount of successfully retrieved elements
 *  	from the get_bugs query
 *  @return A dynamically allocated array of bugzc_bug elements which after
 *  	use most be released from memory with an appropiate call to 
 *  	bugzc_bug_destry_list. */
bugzc_bug *bugzc_bug_get_bugs(bugzc_conn *conn, unsigned int *bug_ids,
				size_t nbugid, size_t *rbugid)
				__attribute__ ((__deprecated__));

/** @brief Gives detailed information about a bugid or an array of bug ids.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param bug_ids An array of numeric bug ids to query from the Bugzilla
 *  	remote installation server.
 *  @param nbugid The amount of elements contained in the bug_ids array.
 *  @param olist An empty bugzc_list where the data will be stored, after use
 * 		this list most freed from memory by calling bigzc_bug_destroy_list2.
 *  @return The amount of elements on the list or a negative value on error. */
int bugzc_bug_get_bugs_list(bugzc_conn *conn, unsigned int *bug_ids,
				size_t nbugid, bugzc_list *olist);

/** @brief Gives detailed information about a specific bug given its id.
 *  @param conn A properly initialized bugz_conn object describing the
 *  	url of the Bugzilla server.
 *  @param bug_id A numeric bug id to query from the Bugzilla
 *  	remote installation server.
 *  @return A pointer to a bugzc_bug object or NULL if an error occurred.
 *  @note The returned bug_bug object must be freed with bugzc_bug_destroy_obj2 */
bugzc_bug *bugzc_bug_get_bug_info(bugzc_conn *conn, unsigned int bug_id);

#ifdef __cplusplus
}
#endif
#endif

