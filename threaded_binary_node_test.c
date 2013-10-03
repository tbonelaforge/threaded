#include <stdio.h>

#include "threaded_binary_node.h"

int main() {
    struct threaded_binary_node * head = new_threaded_binary_head();
    struct threaded_binary_node * node1 = new_threaded_binary_node();
    node1->data = (void *)(long int) 42;
    insert_left_leaf( head, node1 );
    printf( "After adding the first element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head ) );

    struct threaded_binary_node * node2 = new_threaded_binary_node();
    node2->data = (void *)(long int) 43;
    insert_left_leaf( node1, node2 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head ) );

    struct threaded_binary_node * node3 = new_threaded_binary_node();
    node3->data = (void *)(long int) 44;
    insert_right_leaf( node1, node3 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head ) );

    struct threaded_binary_node * successor;

    printf( "The successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( node2 );
    printf( "%s<br />\n", print_threaded_tree( successor ) );

    printf( "The second successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor ) );

    printf( "The third successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor ) );


    printf( "The fourth successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor ) );


    struct threaded_binary_node * predecessor;

    printf( "The predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( node3 );
    printf( "%s<br />\n", print_threaded_tree( predecessor ) );

    printf( "The second predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor ) );

    printf( "The third predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor ) );


    printf( "The fourth predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor ) );

}
