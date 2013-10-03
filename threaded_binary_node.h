#ifndef _THREADED_BINARY_NODE_H_
#define _THREADED_BINARY_NODE_H_

struct threaded_binary_node {
    struct threaded_binary_node * left_link;
    struct threaded_binary_node * right_link;
    char threaded;  // Can be either 'l', 'r', 'b', or 'n'
    void * data;
};

struct threaded_binary_node * new_threaded_binary_node();
struct threaded_binary_node * new_threaded_binary_head();
struct threaded_binary_node * insert_left_leaf( struct threaded_binary_node *, struct threaded_binary_node * );
struct threaded_binary_node * insert_right_leaf( struct threaded_binary_node *, struct threaded_binary_node * );
void delete_right_leaf( struct threaded_binary_node * );
void delete_left_leaf( struct threaded_binary_node * );
void delete_leaf( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_parent( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_left_child( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_right_child( struct threaded_binary_node * );
int is_threaded_left_child( struct threaded_binary_node * );
int is_threaded_right_child( struct threaded_binary_node * );
struct threaded_binary_node * get_leftmost_threaded_descendent( struct threaded_binary_node * );
struct threaded_binary_node * get_rightmost_threaded_descendent( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_successor( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_predecessor( struct threaded_binary_node * );
struct threaded_binary_node * get_second_predecessor( struct threaded_binary_node * );
char * print_threaded_tree( struct threaded_binary_node * );
int has_right_thread( struct threaded_binary_node * );
int has_left_thread( struct threaded_binary_node * );
void add_right_threaded_status( struct threaded_binary_node * );
void add_left_threaded_status( struct threaded_binary_node * );
void remove_right_threaded_status( struct threaded_binary_node * );
void remove_left_threaded_status( struct threaded_binary_node * );
void replace_child( struct threaded_binary_node *, struct threaded_binary_node *, struct threaded_binary_node * );

#endif
