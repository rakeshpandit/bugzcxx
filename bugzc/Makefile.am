#  Bugzilla C/C++ XML-RPC proxy
# 
#  Copyright (C) Juan V. Guerrero 2007
# 
#  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
# 
#  This program is free software, distributed under the terms of
#  the GNU General Public License Version 2. See the LICENSE file
#  at the top of the source tree.

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = bugzc.pc

h_sources = bugzc.h bugzc_version.h bugzc_bugzilla.h bugz_errcodes.h \
	    bugzc_user.h bugzc_bug.h bugzc_product.h bugz_features.h \
	    bugzc_list.h

c_sources = bugzc.c bugzc_bugzilla.c bugz_errcodes.c xmlrpc_helper.c \
	    bugzc_user.c bugzc_bug.c bugzc_product.c \
	    bugzc_list.c

library_includedir=$(includedir)/bugzc

library_include_HEADERS = $(h_sources)

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES=libbugzc.la
libbugzc_la_SOURCES=$(h_sources) $(c_sources)
libbugzc_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all

