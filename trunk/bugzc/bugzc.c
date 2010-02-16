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
#include<string.h>
#include<stdlib.h>

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

int bugzc_init(bugzc_conn *bc, const char *url, size_t surl){
	bc->err_code = 0;
	bc->err_msg = 0;
	/* Validate url using validate_url when it is written */
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
	int surl, i, j, k;
	char vbuf[DEFAULT_VERSION_STRING_SIZE];
	char vmajor[DEFAULT_VERSION_STRING_SIZE] = { 0 };
	char vminor[DEFAULT_VERSION_STRING_SIZE] = { 0 };
	char vpatch[DEFAULT_VERSION_STRING_SIZE] = { 0 };
	bc->err_code = 0;
	bc->err_msg = 0;
	surl = strlen(url);
	/* Validate url using validate_url when it is written */
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
	rpc_void_call_ret_s(bc, "Bugzilla.version", "version", vbuf, DEFAULT_VERSION_STRING_SIZE - 1);
	for(i = 0; vbuf[i] != 0 && vbuf[i] != '.' && i < DEFAULT_VERSION_STRING_SIZE; i++){
		vmajor[i] = vbuf[i];
		vmajor[i + 1] = 0;
	}
	for(++i, j = 0; vbuf[i] != 0 && vbuf[i] != '.' && i < DEFAULT_VERSION_STRING_SIZE; i++, j++){
		vminor[j] = vbuf[i];
		vminor[j + 1] = 0;
	}
	for(++i, k = 0; vbuf[i] != 0 && vbuf[i] <= '9' && vbuf[i] >= '0' && i < DEFAULT_VERSION_STRING_SIZE; i++, k++){
		vpatch[k] = vbuf[i];
		vpatch[k + 1] = 0;
	}
	bc->v_major = atoi(vmajor);
	bc->v_minor = atoi(vminor);
	bc->v_patch = atoi(vpatch);
	return 0;
}

void bugzc_finish(bugzc_conn *bc){
	xmlrpc_client_destroy(bc->xcli);
	free(bc->url);
}
