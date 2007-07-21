#  Bugzilla C/C++ XML-RPC proxy
# 
#  Copyright (C) Juan V. Guerrero 2007
# 
#  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
# 
#  This program is free software, distributed under the terms of
#  the GNU General Public License Version 2. See the LICENSE file
#  at the top of the source tree.

bin_PROGRAMS = getversion gettimezone testlogin

getversion_SOURCES = getversion.c
gettimezone_SOURCES = gettimezone.c
testlogin_SOURCES = testlogin.c

LDADD = ../../bugzc/libbugzc.la $(XMLRPCC_LIBS)
AM_CFLAGS = $(XMLRPCC_CFLAGS)
