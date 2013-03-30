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

#ifndef __BUGZC_LIST_H__
#define __BUGZC_LIST_H__
#include<bugzc/bugzc.h>
/** @file 
 *  Linked list data structure and methods, C does not have native support for
 *  this, so, we have to implement on our own.  */

#ifdef __cplusplus
extern "C" {
#endif
	
/** Linked-list node type definition */
typedef struct bugzc_node_t bugzc_node;

/** Linked list node data structure. */
struct bugzc_node_t {
	/** A pointer to the databuffer to be stored in this data node */
	void *d_ptr;
	/** Holds the size of the buffer pointed by d_ptr. */
	size_t d_size;
	/** A pointer to the next list element, points to 0x0 if this is the
	 *  last one */
	bugzc_node *next;
	/** A pointer to the previous list element, points to 0x0 if this is the
	 *  first one */
	bugzc_node *previous;
};

/** Double-Linked list data structure */
typedef struct bugzc_list_t {
	/** Pointer to the first node on the list */
	bugzc_node *first;
	/** Pointer to the last node on the list */
	bugzc_node *last;
	/** Number of elements on the list */
	int count;
} bugzc_list;

/** @brief Allocates space for a single node.
 *  This function will try to allocate memory for a new node and initialize
 *  its internal data members to proper "safe" values.
 *  @return Null on failure or a pointer to the newly allocated memory space. */
bugzc_node *bugzc_node_alloc();

/** @brief Releases memory previously allocated for a bugzc_node.
 *  Will try to effectively release memory for a given bugzc_node, it will not
 *  deallocate memory for the internal datastore, for that please use
 *  bugzc_node_free_with_data
 *  @param node a reference to a node pointer. */
void bugzc_node_free(bugzc_node **node);

/** @brief Releases memory previously allocated for a bugzc_node and its 
 *  datastore.
 *  Will try to effectively release memory for a given bugzc_node and
 *  deallocate memory for the internal datastore.
 *  @warning It will only perform a free for the internal *d_ptr which 
 *  sometimes is not exactly what you want.
 *  @param node a reference to a node pointer. */
void bugzc_node_free_with_data(bugzc_node **node);

/** @brief Initialzes a bugzc_list doubly-linked list
 *  @param list A pointer to the list to be created
 *  @return A pointer to the list or 0x0 on failure. */
bugzc_list *bugzc_list_init(bugzc_list *list);

/** @brief Destroys a bugzc_list linked list nodes associations only. 
 *  Will delete all nodes in the list one by one without releasing their
 *  datastores, after doing so it will reset the first and last members to 0x0.
 *  @param list A pointer to the list to be freed. */
void bugzc_list_free(bugzc_list *list);

/** @brief Destroys a bugzc_list linked list completely, including all data
 *  stored at each node.
 *  By interatively calling the free(3) function before deleting each node
 *  this function can successfully achieve its goals.
 *  @param list A pointer to the list to be destroyed. */
void bugzc_list_free_with_data(bugzc_list *list);

/** @brief Destroys a bugzc_list linked list completely, including all data
 *  stored at each node.
 *  By interatively calling the destructor function before deleting each node
 *  this function can successfully achieve its goals.
 *  @param list A pointer to the list to be destroyed.
 *  @param destructor A pointer to a function that really "knows" how the perform an
 *  effective free of the data stored at the nodes, by default it is assumed
 *  that the data is homogenous, which means that all data pointed from the 
 *  d_ptr member pointer is of the exact same data type, if that is not the 
 *  case, then this function will fail misserably. The one and only parameter
 *  for the function pointer will be substituted by the node->d_ptr pointer
 *  and if the function could successfully release the data SHOULD return 0x0
 *  any other thing will mean that the memory could not be freed for that
 *  specific node element. */ 
void bugzc_list_free_with_data_destructor(
			bugzc_list *list, void *(*destructor)(void *node_elem));

/** @brief Will look for the node at position idx.
 *  Searches a nth node ocated at the position idx of the list from the top
 *  to bottom of the list, however if the idx is a negative number it will
 *  perform the search backwards.
 *  @param list The list we are examining.
 *  @param idx The nth position at where our node is located, if the value is
 *  negative then it will be translated as the position from the last to
 *  the first element on the list.
 *  @return If there is an element at that position it will return a pointer
 *  to it, if not then or if an error occurs it will return 0x0 */
bugzc_node *bugzc_list_at_index(bugzc_list *list, int idx);

/** @brief Will append a bugzc_node to the end of the list.
 *  @param list The list we are using.
 *  @param node The node to append.
 *  @return A pointer to the list or 0x0 on error. */
bugzc_list *bugzc_list_append_node(bugzc_list *list, bugzc_node *node);

/** @brief Appends to the end of a list a new node with the given data.
 *  It will, at first, create a new detached node and assign the data values
 *  to end, then will append the node to the end of the list updating any
 *  list links as required.
 *  @param list Whe list which we want to extend.
 *  @param d_ptr A pointer to the data we are putting in the node to be
 * 			 created for it
 *  @param d_size The size of the data in bytes
 *  @return A pointer to the list or 0x0 on error. */
bugzc_list *bugzc_list_append_data(bugzc_list *list, void *d_ptr, 
									size_t d_size);
#ifdef __cplusplus
}
#endif
#endif
