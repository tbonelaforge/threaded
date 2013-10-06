#ifndef _THREADED_BINARY_NODE_H_
#define _THREADED_BINARY_NODE_H_

/*============================================================

Definition: threaded_binary_node

Binary node, where the link fields are sometimes used to 
point to successors or predecessors.  
See Knuth's TAOCP for more info.

============================================================*/


struct threaded_binary_node {
    struct threaded_binary_node * left_link;
    struct threaded_binary_node * right_link;
    char threaded;  // Can be either 'l', 'r', 'b', or 'n'
    int height; // The height of this tree, including this node.
    void * data;
};

/*============================================================

Definition: ptr2comparator

A pointer to a function of ( void *, void * ),
which is expected to return -1, 0, or 1.

============================================================*/

typedef int (*ptr2comparator)( void *, void * );

/*============================================================

Definition: ptr2dataprinter

A pointer to a function of ( void *),
which is expected to return a pointer to a newly-allocated, null-terminated array of characters.

============================================================*/

typedef char * (*ptr2dataprinter)( void * );

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
struct threaded_binary_node * get_threaded_child( struct threaded_binary_node *, int );
int is_threaded_left_child( struct threaded_binary_node * );
int is_threaded_right_child( struct threaded_binary_node * );
struct threaded_binary_node * get_leftmost_threaded_descendent( struct threaded_binary_node * );
struct threaded_binary_node * get_rightmost_threaded_descendent( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_successor( struct threaded_binary_node * );
struct threaded_binary_node * get_threaded_predecessor( struct threaded_binary_node * );
struct threaded_binary_node * get_second_predecessor( struct threaded_binary_node * );
char * print_threaded_tree( struct threaded_binary_node *, ptr2dataprinter );
int has_right_thread( struct threaded_binary_node * );
int has_left_thread( struct threaded_binary_node * );
void add_right_threaded_status( struct threaded_binary_node * );
void add_left_threaded_status( struct threaded_binary_node * );
void remove_right_threaded_status( struct threaded_binary_node * );
void remove_left_threaded_status( struct threaded_binary_node * );
void replace_child( struct threaded_binary_node *, struct threaded_binary_node *, struct threaded_binary_node * );
void rotate_left( struct threaded_binary_node * );
void rotate_right( struct threaded_binary_node * );
void rotate( struct threaded_binary_node *, int );
struct threaded_binary_node * threaded_search( struct threaded_binary_node *, void *, ptr2comparator );
struct threaded_binary_node * threaded_insert( struct threaded_binary_node *, void *, ptr2comparator );
void calculate_threaded_height( struct threaded_binary_node * );
int is_threaded_head( struct threaded_binary_node * );
void balance( struct threaded_binary_node * );
int is_balanced( struct threaded_binary_node * );
int get_threaded_child_height( struct threaded_binary_node *, int );
int get_threaded_height( struct threaded_binary_node * );
int get_heavy_child_index( struct threaded_binary_node * );
struct threaded_binary_node * insert( struct threaded_binary_node * , void *, ptr2comparator );

#endif
