#ifndef _TREAP_H_
#define _TREAP_H_

#include "threaded_binary_node.h"

struct treap_data {
    int priority;
    char value;
};

struct treap_data * new_treap_data();
struct threaded_binary_node * insert( struct threaded_binary_node *, char );
void perform_rotations( struct threaded_binary_node * );
void rotate_right( struct threaded_binary_node * );
void rotate_left( struct threaded_binary_node * );
struct threaded_binary_node * search( struct threaded_binary_node *, char );
struct threaded_binary_node * get_highest_priority_child( struct threaded_binary_node * );
int compare( struct treap_data *, struct treap_data * );
int is_dominated( struct threaded_binary_node *, struct threaded_binary_node * );
struct threaded_binary_node * get_highest_priority_child( struct threaded_binary_node * );

#endif // ifndef _TREAP_H_
