#  Bugzilla C/C++ XML-RPC proxy
# 
#  Copyright (C) Juan V. Guerrero 2007
# 
#  Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
# 
#  This program is free software, distributed under the terms of
#  the GNU General Public License Version 2. See the LICENSE file
#  at the top of the source tree.

bin_PROGRAMS = getversion gettimezone testlogin get_legal_field_values \
				submit_bug get_bugs offer_account_by_email bugz_create_user \
				get_products

getversion_SOURCES = getversion.c utils.c

gettimezone_SOURCES = gettimezone.c utils.c

testlogin_SOURCES = testlogin.c utils.c

get_legal_field_values_SOURCES = get_legal_field_values.c utils.c

submit_bug_SOURCES = submit_bug.c utils.c

get_bugs_SOURCES = get_bugs.c utils.c

offer_account_by_email_SOURCES = offer_account_by_email.c utils.c

bugz_create_user_SOURCES = bugz_create_user.c utils.c

get_products_SOURCES = get_products.c utils.c

LDADD = ../../bugzc/libbugzc.la $(XMLRPCC_LIBS)
AM_CFLAGS = $(XMLRPCC_CFLAGS) 
AM_CPPFLAGS = -I$(top_srcdir)
