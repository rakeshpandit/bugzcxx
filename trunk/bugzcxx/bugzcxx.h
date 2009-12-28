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

#ifndef __BUGZCXX_H__
#define __BUGZCXX_H__
#include<bugzc/bugzc_version.h>
#include<bugzc/bugz_features.h>
#include<bugzcxx/Exception.h>
#include<string>
#include<memory>

/** Holds the Bugzilla C/C++ XML-RPC proxy C++ implementation. */
namespace bugzcxx {

	/** @brief Represents a "live" connection to a Bugzilla bug tracking
	 *  system.
	 *  Implements Bugzilla::WebService::Bugzilla namespace as defined in:
	 *  http://www.bugzilla.org/docs/tip/html/api/Bugzilla/WebService/Bugzilla.html
	 *  An also a few methods from Bugzilla::WebService::User like login() and
	 *  logout.
	 *  @note To open a session to a Bugzilla server instace you must start by
	 *  instantiating an object of this class and interact with it to 
	 *  obtain/submit the required information to it.
	 *  From a connection object you can login/logout to the server, request
	 *  product parameter information, submit bugs, etc. This class allows you
	 *  to do almost anything. */
	class Connection {
		private:
			/** @brief Holds the user's current session id */
			int sess_id;
			/** @brief Opaque data type for low-level connection info. */
			class Info;
			//Info *cInfo;
			std::auto_ptr<Info> cInfo;
		protected:
		public:
			/** @brief Mandatory default constructor, it only initializes some
			 *  internal variables.
			 *  @note This method won't attempt to make a real connection, you 
			 *  must login for that first. */
			Connection();
			/** @brief Instantiates a connection object a logs a user into the 
			 *  specified Bugzilla server.
			 *  @warning While attempting to login this method might throw an
			 *  exception, it is recommended to take all needed measures to
			 *  trap it safely.
			 *  @param url Corresponds to the internet location where to
			 *  server's xmlrpc cgi script is.
			 *  @param username A valid Bugzilla username, most commonly a
			 *  e-mail address.
			 *  @param password The user's password. */
			Connection(const std::string &url, 
					const std::string &username,
					const std::string &password
					);
			/** @brief Copy constructor. */
			Connection(const bugzcxx::Connection &c);
			/** @brief Will release all memory used by this class, however, it
			 *  WILL NOT logout the user. */
			~Connection();
			/** @brief Logs the specified user into the Bugzilla server.
			 *  @param url Corresponds to the internet location where to
			 *  server's xmlrpc cgi script is.
			 *  @param username A valid Bugzilla username, most commonly a
			 *  e-mail address.
			 *  @param password The user's password.
			 *  @param remember If non-zero the login cookie will expire after 
			 *  the session	closes, otherwise it will outlive 
			 *  the user's session.
			 *  @return The user's numeric ID. */
			int login(const std::string &url, 
						const std::string &username,
						const std::string &password,
						int remember = 0
						);
			/** @brief Closes a previous session to the Bugzilla server. */
			void logout();
			/** @brief Retrieves the Bugzilla software version installed at
			 *  the server.
			 *  @return A std::string containing the server's Bugzilla
			 *  version. */
			std::string version();
			/** @brief Retrieves the timezone at server's location.
			 *  @return A std::string containing the timezone. */ 
			std::string timezone();
	};
};

#endif
