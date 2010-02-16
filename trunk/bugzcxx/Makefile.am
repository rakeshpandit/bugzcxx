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
pkgconfig_DATA = bugzcxx.pc

h_sources = bugzcxx.h Exception.h BugInfo.h

cc_sources = bugzcxx.cpp Exception.cpp BugInfo.cpp

library_includedir=$(includedir)/bugzcxx

library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_dir) -I.. -I.

lib_LTLIBRARIES=libbugzcxx.la
libbugzcxx_la_SOURCES=$(h_sources) $(cc_sources)
libbugzcxx_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all
