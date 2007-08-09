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
#include"bugzc.h"
#include"bugz_errcodes.h"
#include"bugzc_list.h"
#include<string.h>
#include<stdlib.h>

extern const char *_bugz_errmsg[];

bugzc_node *bugzc_node_alloc(){
	bugzc_node *node = 0;
	
	node = malloc(sizeof(bugzc_node));
	if(node){
		node->d_ptr = 0;
		node->d_size = 0;
		node->previous = 0;
		node->next = 0;
	}
	
	return node;
}

void bugzc_node_free(bugzc_node **node){
	free(*node);
	*node = 0;
}

void bugzc_node_free_with_data(bugzc_node **node){
	bugzc_node *n;
	n = *node;
	if(n->d_ptr != 0){
		free(n->d_ptr);
	}
	free(*node);
	*node = 0;
}

bugzc_list *bugzc_list_create(bugzc_list *list){
	list->first = 0;
	list->last = 0;
	list->count = 0;
}

void bugzc_list_free(bugzc_list *list){
	bugzc_node *f, *tmp;
	f = list->first;
	while(f != 0){
		tmp = f;
		f = f->next;
		bugzc_node_free(&tmp);
	}
	list->first = 0;
	list->last = 0;
	list->count = 0;
}

void bugzc_list_free_with_data(
			bugzc_list *list){
	bugzc_node *f, *tmp;
	f = list->first;
	while(f != 0){
		tmp = f;
		f = f->next;
		free(tmp->d_ptr);
		bugzc_node_free(&tmp);
	}
	list->first = 0;
	list->last = 0;
	list->count = 0;
}

void bugzc_list_free_with_data_destructor(
			bugzc_list *list, void *(*destructor)(void *node_elem)){
	bugzc_node *f, *tmp;
	f = list->first;
	while(f != 0){
		tmp = f;
		f = f->next;
		destructor(tmp->d_ptr);
		bugzc_node_free(&tmp);
	}
	list->first = 0;
	list->last = 0;
	list->count = 0;
}

bugzc_node *bugzc_list_at_index(bugzc_list *list, int idx){
	bugzc_node *f;
	int i = 0;
	f = list->first;
	while(f != 0 && i <= idx){
		f = f->next;
		i++;
	}
	return f;
}

bugzc_list *bugzc_list_append_node(bugzc_list *list, bugzc_node *node){
	if(list->first == 0){
		list->first = node;
		list->last = node;
	}
	else{
		node->next = 0;
		node->previous = list->last;
		list->last->next = node;
		list->last = node;
	}
	list->count++;
	return list;
}

bugzc_list *bugzc_list_append_data(bugzc_list *list, void *d_ptr, 
									size_t d_size){
	
	bugzc_node *node;
	
	node = bugzc_node_alloc();
	if(node == 0){
		return 0x0;
	}
	node->d_ptr = d_ptr;
	node->d_size = d_size;
	return bugzc_list_append_node(list, node);
}

