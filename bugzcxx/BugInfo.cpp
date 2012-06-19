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
#include<cstring>
#include<cstdlib>
#include"BugInfo.h"


namespace bugzcxx {

	BugInfo::BugInfo(){
		_id = -1;
	}

	BugInfo::BugInfo(const BugInfo &b){
		_id = b._id;
		_alias = b._alias;
		_summary = b._summary;
		_creation_time = b._creation_time;
		_last_change_time = b._last_change_time;
		_creation_tstamp = b._creation_tstamp;
		_last_change_tstamp = b._last_change_tstamp;
	}

	BugInfo::BugInfo(const bugzc_bug &b){
		_id = b.id;
		_alias = b.alias;
		_summary = b.summary;
		_creation_time = b.creation_time;
		_last_change_time = b.last_change_time;
		_creation_tstamp = b.creation_tstamp;
		_last_change_tstamp = b.last_change_tstamp;
	}

	BugInfo::~BugInfo() {

	}

	BugInfo &BugInfo::operator=(const bugzc_bug &b){
		_id = b.id;
		_alias = b.alias;
		_summary = b.summary;
		_creation_time = b.creation_time;
		_last_change_time = b.last_change_time;
		_creation_tstamp = b.creation_tstamp;
		_last_change_tstamp = b.last_change_tstamp;
		return *this;
	}

	unsigned int BugInfo::id(){
		return _id;
	}

	const std::string &BugInfo::summary(){
		return _summary;
	}

	const std::string &BugInfo::alias(){
		return _alias;
	}

	const std::string &BugInfo::creationTimeS(){
		return _creation_time;
	}

	const std::string &BugInfo::lastChangeTimeS(){
		return _last_change_time;
	}
}
