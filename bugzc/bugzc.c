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

#include"config.h"
#include<bugzc/bugzc.h>
#include<bugzc/xmlrpc_helper.h>
#include<xmlrpc-c/client.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#ifndef BUGZCXX_CLIENT_NAME
#define BUGZCXX_CLIENT_NAME "bugzcxx"
#endif

#ifndef DEFAULT_VERSION_STRING_SIZE
#define  DEFAULT_VERSION_STRING_SIZE 12
#endif

extern const char *_bugz_errmsg[];

static const char *__curl_transport = "curl";

/* @todo: Write a function that can validate urls */
/* static int validate_url(const char *url, size_t surl){ */
/* 	/\* regex: http[s]?:\/\/[a-zA-Z0-9]*{\.[a-zA-Z0-9].....*\/ */
/* 	return 1; */
/* } */

static struct xmlrpc_clientparms global_xparms;

int bugzc_init2(bugzc_conn *bconn, const char *url){
	size_t length;
	char *vmajor;
	char *vminor;
	char *vpatch;
	char vbuf[DEFAULT_VERSION_STRING_SIZE];
	struct xmlrpc_curl_xportparms curl_parms;
	memset(&curl_parms, 0, sizeof(curl_parms));
	/* Temporary hack to skip CA certificate checks. Useful for
	   devlopment.*/
	/* curl_parms.no_ssl_verifypeer = 1; */
	/* curl_parms.no_ssl_verifyhost = 1; */
	curl_parms.user_agent = BUGZCXX_CLIENT_NAME"/"BUGZCXX_VERSION_STRING;

	bconn->err_code = 0;
	bconn->err_msg = 0;
	length = strlen(url);
	/* Validate url using validate_url when it is written */
	bconn->url = malloc(length + 1);
	strncpy(bconn->url, url, length);
	bconn->url[length] = '\0';

	/* Need a solution here for skipping CA certificate checks. */
	/* We can extend xmlrpc-c library no_ssl_verifypeer here. */
	memset(&global_xparms, 0, sizeof(global_xparms));
	global_xparms.transportparmsP = &curl_parms;
	global_xparms.transport = __curl_transport;
	global_xparms.transportparm_size = XMLRPC_CXPSIZE(user_agent);

	xmlrpc_env_init(&bconn->xenv);

	/* 733402 byte long response has issues. Increasing limit to 2*512k */
	xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID, 2*XMLRPC_XML_SIZE_LIMIT_DEFAULT);
	xmlrpc_client_setup_global_const(&bconn->xenv);

	xmlrpc_client_create(&bconn->xenv, XMLRPC_CLIENT_NO_FLAGS,
			BUGZCXX_CLIENT_NAME, BUGZCXX_VERSION_STRING, 
			&global_xparms, 
			XMLRPC_CPSIZE(transportparm_size), &bconn->xcli);

	rpc_void_call_ret_s(bconn, "Bugzilla.version", "version", vbuf, DEFAULT_VERSION_STRING_SIZE - 1);
	vmajor = strtok(vbuf, ".");
	bconn->v_major = vmajor ? atoi(vmajor) : 0;
	vminor = strtok(NULL, ".");
	bconn->v_minor = vminor ? atoi(vminor) : 0;
	vpatch = strtok(NULL, ".");
	bconn->v_patch = vpatch ? atoi(vpatch) : 0;
	return 0;
}

void bugzc_finish(bugzc_conn *bconn){
	xmlrpc_client_destroy(bconn->xcli);
	free(bconn->url);
}
