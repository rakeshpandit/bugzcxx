dnl  Bugzilla C/C++ XML-RPC proxy
dnl 
dnl  Copyright (C) Juan V. Guerrero 2007
dnl 
dnl  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
dnl 
dnl  This program is free software, distributed under the terms of
dnl  the GNU General Public License Version 2. See the LICENSE file
dnl  at the top of the source tree.

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------


AC_INIT(bugzc/bugzc.h)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------
GENERIC_LIBRARY_NAME=bugzcxx
BUGZC_LIBRARY_NAME=bugzc
BUGZCXX_LIBRARY_NAME=bugzcxx

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=0
GENERIC_MICRO_VERSION=2
GENERIC_PATCH_LEVEL=0
AC_SUBST(GENERIC_MAJOR_VERSION)
AC_SUBST(GENERIC_MINOR_VERSION)
AC_SUBST(GENERIC_MICRO_VERSION)
AC_SUBST(GENERIC_PATCH_LEVEL)


GENERIC_LIBRARY_VERSION=$GENERIC_MINOR_VERSION:$GENERIC_MICRO_VERSION:$GENERIC_PATCH_LEVEL
GENERIC_LIBRARY_VERSION_DOTTED=$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL

AC_SUBST(GENERIC_LIBRARY_VERSION)
AC_SUBST(GENERIC_LIBRARY_VERSION_DOTTED)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(BUGZC_LIBRARY_NAME)
AC_SUBST(BUGZCXX_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_LANG_CPLUSPLUS

CXXFLAGS="$CXXFLAGS -Wall "

dnl -----------------------------------------------
dnl Verify manual features
dnl -----------------------------------------------

LIBS="$LIBS -ldl"

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug          Build library in debug mode]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		debug_mode_activated=on
		AC_MSG_RESULT([ *** This library will be compiled with debug support activated *** ])
		CPPFLAGS="$CPPFLAGS -DUSE_DEBUG"
	], [
		debug_mode_activated=off
	]
)

BUILD_CXX_DIR=bugzcxx

AC_ARG_ENABLE(cxx, AC_HELP_STRING([--disable-cxx           Don't compile C++ support library]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		cxx_support=off
		BUILD_CXX_DIR=""
		AC_MSG_RESULT([ *** This library will not include C++ support libraries *** ])
	], [
		cxx_support=on
	]
)

CXX_EXAMPLES_DIR=bugzcxx
EXAMPLES_DIR=examples
AC_ARG_ENABLE(examples, AC_HELP_STRING([--disable-examples      Don't compile example programs]), [
		AC_DEFINE(USE_DEBUG, 1, [Activates debug mode])
		build_examples=off
		CXX_EXAMPLES_DIR=""
		EXAMPLES_DIR=""
		AC_MSG_RESULT([ *** This library will not build any example programs *** ])
	], [
		build_examples=on
	]
)

AC_SUBST(BUILD_CXX_DIR)
AC_SUBST(CXX_EXAMPLES_DIR)
AC_SUBST(EXAMPLES_DIR)

dnl
dnl xmlrpc-c stuff
dnl
AC_PATH_PROG([XMLRPC_C_CONFIG], [xmlrpc-c-config], no_xmlrpc, [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin]
	     )

XMLRPC_C_VERSION=""
XMLRPC_C_VERSION_NUM=""
if test "no$XMLRPC_C_CONFIG" = "nono_xmlrpc" 
then
	echo "xmlrpc-c-config not found, install xmlrpc-c first. http://xmlrpc-c.sourceforge.net"
	exit 1
else
	echo "Verifying that xmlrpc-c has been compiled with the curl transport..."
	$XMLRPC_C_CONFIG --features | grep "curl-client" > /dev/null 2>&1
	if test $? -ne 0
	then
		echo "xmlrpc-c was not compiled with cUrl transport, it is imperative to have it since Bugzilla's web services requires cookie handling"
		exit 1
	fi
	XMLRPC_C_VERSION=`$XMLRPC_C_CONFIG --version`
fi


XMLRPCC_CFLAGS=`$XMLRPC_C_CONFIG client --cflags`
XMLRPCC_LIBS=`$XMLRPC_C_CONFIG client --libs`

AC_SUBST(XMLRPCC_CFLAGS)
AC_SUBST(XMLRPCC_LIBS)
AC_SUBST(XMLRPC_C_VERSION)
AC_SUBST(XMLRPC_C_VERSION_NUM)


dnl -----------------------------------------------------------
dnl Doxygen stuff
dnl 1. Detect doxygen path
dnl 2. Verify of the user wants to build the docs automatically
dnl -----------------------------------------------------------
AC_PATH_PROG([DOXYGEN], [doxygen], docs, []
             [$PATH:/usr/local/bin:/opt:/opt/doxygen:/bin:/opt/bin:/opt/sfw/bin:/usr/ccs/bin])

AC_SUBST(DOXYGEN)


API_DOCS_DIR=api
AC_ARG_ENABLE(docs, AC_HELP_STRING([--enable-docs           Build library documentation]), [
		DOXYGEN_INPUT_DIR="api"
		doxygen_docs=yes
		API_DOCS_DIR=api
],[
		DOXYGEN_INPUT_DIR=""
		doxygen_docs=no
		API_DOCS_DIR=""
])
AC_SUBST(DOXYGEN_INPUT_DIR)
AC_SUBST(API_DOCS_DIR)


dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
          bugzc/Makefile \
          bugzc/bugzc.pc \
          bugzc/bugzc_version.h \
          bugzcxx/Makefile \
          bugzcxx/bugzcxx.pc \
	  api/Makefile \
	  api/bugzc/Makefile \
	  api/bugzc/Doxyfile \
	  api/bugzcxx/Makefile \
	  api/bugzcxx/Doxyfile \
	  examples/Makefile \
	  examples/bugzc/Makefile \
	  examples/bugzcxx/Makefile
)

echo
echo "######################################"
echo "# Bugzilla C/C++ XML-RPC Proxy $GENERIC_VERSION"
echo "#"
echo "#  Platform:              $host"
echo "#  Debug mode:            $debug_mode_activated"
echo "#  Generate docs:         $doxygen_docs"
echo "#  Build C++ support:     $cxx_support"
echo "#  xmlrpc-c version:      $XMLRPC_C_VERSION"
echo "#  Build examples:        $build_examples"
