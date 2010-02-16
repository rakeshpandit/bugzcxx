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

#ifndef __BUGINFO_H__
#define __BUGINFO_H__
#include<string>
#include "bugzc/bugzc_bug.h"

namespace bugzcxx {

	/** Describes all bug fields.
	 *  @see bugzc_bug */
	class BugInfo {
		protected:
			unsigned int _id;
			std::string _alias;
			std::string _summary;
			std::string _creation_time;
			std::string _last_change_time;
			/** Bug creation date/time as a unix timestamp */
			time_t _creation_tstamp;
			/** Bug last modification date/time as a unix timestamp */
			time_t _last_change_tstamp;
		public:
			BugInfo();
			/** Copy constructor, it builds from another BugInfo object */
			BugInfo(const BugInfo &b);
			/** Copy constructor, it builds from a bugzc_bug structure */
			BugInfo(const bugzc_bug &b);
			virtual ~BugInfo();
			/** Assignment operator, it copies data from a bugzc_bug
			 *  structure */
			BugInfo &operator=(const bugzc_bug &b);
			/** Use it to get retrieve the bug's Id from bugzilla.
			 *  @return The bug's numeric Id.*/
			unsigned int id();
			/** Use it to get retrieve the first bug alias from bugzilla.
			 *  @return The bug's first alias as a std::string.*/
			const std::string &alias();
			/** Use it to get retrieve summary information from the bug.
			 *  @return The bug's summary as a std::string*/
			const std::string &summary();
			/** Use it to get retrieve the bug's creation time and date as
			 *  a string.
			 *  @return A string representing the bug's creation
			 *  time and date */
			const std::string &creationTimeS();
			/** Use it to get retrieve the bug's last change time and date.
			 *  @return A string representing the bug's last change
			 *  time and date */
			const std::string &lastChangeTimeS();
			/** Use it to get retrieve the bug's creation time and date as
			 *  a time_t value.
			 *  @return A string representing the bug's creation
			 *  time and date */
			time_t creationTime();
			/** Use it to get retrieve the bug's last change time and date.
			 *  @return A time_t representing the bug's last change
			 *  time and date */
			time_t lastChangeTime();
	};

}

#endif
