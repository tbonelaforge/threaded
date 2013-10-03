#ifndef _HEAP_H_
#define _HEAP_H_

#include "threaded_binary_node.h"


struct heap {
    struct threaded_binary_node * head;
    struct threaded_binary_node * tail;
};

struct heap * new_heap();
int is_dominated( struct threaded_binary_node *, struct threaded_binary_node * );
void bubble_value_up( struct threaded_binary_node * );
struct heap * heap_insert( struct heap *, void * );
void * extract_min( struct heap * );
void bubble_value_down( struct threaded_binary_node * );
struct threaded_binary_node * get_highest_priority_child( struct threaded_binary_node * );

#endif
