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
#include<string.h>
#include<stdlib.h>

#ifndef BUGZCXX_CLIENT_NAME
#define BUGZCXX_CLIENT_NAME "bugzcxx"
#endif

extern const char *_bugz_errmsg[];

static const char *__curl_transport = "curl";

/***************************************************************************/
static int validate_url(const char *url, size_t surl){
	/** @todo: Write a function that can validate urls */
	/* regex: http[s]?:\/\/[a-zA-Z0-9]*{\.[a-zA-Z0-9].....*/
	return 1;
}

static struct xmlrpc_clientparms global_xparms;

int bugzc_init(bugzc_conn *bc, const char *url, size_t surl){
	bc->err_code = 0;
	bc->err_msg = 0;
	if(!validate_url(url, surl)){
		bc->url = 0;
		return -1;
	}
	bc->url = malloc(surl + 1);
	strncpy(bc->url, url, surl);
	bc->url[surl] = '\0';
	global_xparms.transport = __curl_transport;
	xmlrpc_env_init(&bc->xenv);
	xmlrpc_client_setup_global_const(&bc->xenv);

	xmlrpc_client_create(&bc->xenv, XMLRPC_CLIENT_NO_FLAGS, 
			BUGZCXX_CLIENT_NAME, BUGZCXX_VERSION_STRING, 
			&global_xparms, 
			sizeof(global_xparms), &bc->xcli);
	return 0;
}

int bugzc_init2(bugzc_conn *bc, const char *url){
	int surl;
	bc->err_code = 0;
	bc->err_msg = 0;
	surl = strlen(url);
	if(!validate_url(url, surl)){
		bc->url = 0;
		return -1;
	}
	bc->url = malloc(surl + 1);
	strncpy(bc->url, url, surl);
	bc->url[surl] = '\0';
	global_xparms.transport = __curl_transport;
	xmlrpc_env_init(&bc->xenv);
	xmlrpc_client_setup_global_const(&bc->xenv);

	xmlrpc_client_create(&bc->xenv, XMLRPC_CLIENT_NO_FLAGS, 
			BUGZCXX_CLIENT_NAME, BUGZCXX_VERSION_STRING, 
			&global_xparms, 
			sizeof(global_xparms), &bc->xcli);
	return 0;
}

void bugzc_finish(bugzc_conn *bc){
	xmlrpc_client_destroy(bc->xcli);
	free(bc->url);
}
