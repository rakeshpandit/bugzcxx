#  Bugzilla C/C++ XML-RPC proxy
# 
#  Copyright (C) Juan V. Guerrero 2009
# 
#  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
# 
#  This program is free software, distributed under the terms of
#  the GNU General Public License Version 2. See the LICENSE file
#  at the top of the source tree.

bin_PROGRAMS = testlogin accountoffer getbuginfo

testlogin_SOURCES = testlogin.cpp utils.cpp

accountoffer_SOURCES =  accountoffer.cpp utils.cpp

getbuginfo_SOURCES = getbuginfo.cpp utils.cpp

LDADD = ../../bugzcxx/libbugzcxx.la ../../bugzc/libbugzc.la $(XMLRPCC_LIBS)
AM_CFLAGS = $(XMLRPCC_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)
