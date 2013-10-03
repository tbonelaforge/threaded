#include <stdio.h>
#include <string.h>
#include "heap.h"

int main() {
    struct heap * test_heap = new_heap();

    struct threaded_binary_node * node1 = new_threaded_binary_node();
    node1->data = (void *)(long int) 54;
    insert_left_leaf( test_heap->head, node1 );
    printf( "After adding the first element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( test_heap->head ) );

    struct threaded_binary_node * node2 = new_threaded_binary_node();
    node2->data = (void *)(long int) 33;
    insert_left_leaf( node1, node2 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( test_heap->head ) );

    struct threaded_binary_node * node3 = new_threaded_binary_node();
    node3->data = (void *)(long int) 42;
    insert_right_leaf( node1, node3 );
    printf( "After adding the third element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( test_heap->head ) );

    printf( "About to bubble value up from node3 ( 42 )\n" );
    bubble_value_up( node3 );
    printf( "After bubbling, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( test_heap->head ) );


    printf( "About to bubble value up from node2 ( 33 )\n" );
    bubble_value_up( node2 );
    printf( "After bubbling, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( test_heap->head ) );


    printf( "About to start a new heap from scratch.<br />\n" );
    struct heap * my_heap = new_heap();

    printf( "After inserting one element ( 5 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 5 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 6 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 6 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 4 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 4 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 7 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 7 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 3 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 3 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 8 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 8 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 2 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 2 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 10 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 10 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );

    printf( "After inserting one element ( 1 ), the heap's tree looks like:<br />\n" );
    heap_insert( my_heap, (void *)(long int) 1 );
    printf( "%s<br />\n", print_threaded_tree( my_heap->head ) );


}
