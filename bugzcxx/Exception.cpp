/*
 *  Bugzilla C/C++ XML-RPC proxy
 *
 *  Copyright (C) Juan V. Guerrero 2009
 *
 *  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 *  This program is free software, distributed under the terms of
 *  the GNU General Public License Version 2. See the LICENSE file
 *  at the top of the source tree.
 */
#include"Exception.h"

namespace bugzcxx {

	Exception::Exception(){
		_code = -1;
	}

	Exception::Exception(int __code, const std::string &__msg){
		_code = __code;
		_msg = __msg;
	}

	int Exception::code(){
		return _code;
	}

	const std::string &Exception::message(){
		return _msg;
	}

	XmlRPCException::XmlRPCException(){

	}

	XmlRPCException::XmlRPCException(int __code, const std::string &__msg) : Exception(__code, __msg) {

	}
}
