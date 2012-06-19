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

#ifndef __BUGZCXX_EXCEPTION_H__
#define __BUGZCXX_EXCEPTION_H__
#include<string>

namespace bugzcxx {

	/** @brief Main exception superclass, thrown whenever a generic error
	 *  occurs. */
	class Exception {
		private:
		protected:
			int _code;
			std::string _msg;
		public:
			Exception();
			/** @brief Instantiates an exception object with the given error
			 *  code and error message.
			 *  @param __code Numeric error which this exceotion is 
			 *  representing.
			 *  @param __msg Error message which describes a human 
			 *  understandable reason why this exception was thrown. */ 
			Exception(int __code, const std::string &__msg);
			/** @brief Retrieves the error code related to this exception.
			 *  @return The error's numeric error code. */
			int code();
			/** @brief Retrieves a message related to the reason why the
			 *  exception was thrown.
			 *  @return The error message. */
			const std::string &message();
	};
	
	/** @brief Exception thrown whenever an error occurred at the XML-RPC 
	 *  level. */ 
	class XmlRPCException : public Exception {
		public:
			XmlRPCException();
			/** @brief Instantiates an exception object with the given error
			 *  code and error message.
			 *  @param __code Numeric error which this exceotion is 
			 *  representing.
			 *  @param __msg Error message which describes a human 
			 *  understandable reason why this exception was thrown. */
			XmlRPCException(int __code, const std::string &__msg);
	};
};

#endif
