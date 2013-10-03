#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "threaded_binary_node.h"

/*============================================================
Data printer to be used during testing 
============================================================*/
char * print_data_as_integer( void * );

/*============================================================

Testing routine for inserts

============================================================*/
void test_three_inserts( int, int, int );

/*============================================================

Main testing routine.

============================================================*/



int main() {
    struct threaded_binary_node * head = new_threaded_binary_head();
    struct threaded_binary_node * node1 = new_threaded_binary_node();
    node1->data = (void *)(long int) 42;
    insert_left_leaf( head, node1 );
    printf( "After adding the first element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head, &print_data_as_integer ) );

    struct threaded_binary_node * node2 = new_threaded_binary_node();
    node2->data = (void *)(long int) 43;
    insert_left_leaf( node1, node2 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head, &print_data_as_integer ) );

    struct threaded_binary_node * node3 = new_threaded_binary_node();
    node3->data = (void *)(long int) 44;
    insert_right_leaf( node1, node3 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    printf( "%s<br />\n", print_threaded_tree( head, &print_data_as_integer ) );

    struct threaded_binary_node * successor;

    printf( "The successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( node2 );
    printf( "%s<br />\n", print_threaded_tree( successor, &print_data_as_integer ) );

    printf( "The second successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor, &print_data_as_integer ) );

    printf( "The third successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor, &print_data_as_integer ) );


    printf( "The fourth successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    printf( "%s<br />\n", print_threaded_tree( successor, &print_data_as_integer ) );


    struct threaded_binary_node * predecessor;

    printf( "The predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( node3 );
    printf( "%s<br />\n", print_threaded_tree( predecessor, &print_data_as_integer ) );

    printf( "The second predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor, &print_data_as_integer ) );

    printf( "The third predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor, &print_data_as_integer ) );


    printf( "The fourth predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    printf( "%s<br />\n", print_threaded_tree( predecessor, &print_data_as_integer ) );

    printf( "About to test the insertion of 42, 43, and 44\n" );
    test_three_inserts( 42, 43, 44 );

    printf( "About to test the insertion of 42, 44, and 43\n" );
    test_three_inserts( 42, 44, 43 );

    printf( "About to test the insertion of 43, 42, and 44\n" );
    test_three_inserts( 43, 42, 44 );

    printf( "About to test the insertion of 43, 44, and 42\n" );
    test_three_inserts( 43, 44, 42 );

    printf( "About to test the insertion of 44, 42, and 43\n" );
    test_three_inserts( 44, 42, 43 );

    printf( "About to test the insertion of 44, 43, and 42\n" );
    test_three_inserts( 44, 43, 42 );

}



char * print_data_as_integer( void * value ) {
    long int printable = (long int) value; // Perform the cast.
    int howmanydigits = 1;
    if ( printable > 0 ) {
        howmanydigits = ceil( log10( (double) printable ) );
    }
    char * data_string = malloc( ( howmanydigits + 1 ) * sizeof( char ) );
    *data_string = '\0';
    sprintf( data_string, "%ld", printable );
    return data_string;
    
}


/*============================================================

Comparator to be used when searching and inserting.

============================================================*/

int compare_data_as_integers( void *, void * );

void test_three_inserts( int a, int b, int c ) {
    struct threaded_binary_node * head = new_threaded_binary_head();
    void * data_a = (void *)(long int) a;
    void * data_b = (void *)(long int) b;
    void * data_c = (void *)(long int) c;
    
    threaded_insert( head, data_a, &compare_data_as_integers );
    printf( "After inserting %d, the tree looks like: <br />\n%s", a, print_threaded_tree( head, &print_data_as_integer ) );
    threaded_insert( head, data_b, &compare_data_as_integers );
    printf( "After inserting %d, the tree looks like: <br />\n%s", b, print_threaded_tree( head, &print_data_as_integer ) );
    threaded_insert( head, data_c, &compare_data_as_integers );
    printf( "After inserting %d, the tree looks like: <br />\n%s", c, print_threaded_tree( head, &print_data_as_integer ) );
}

int compare_data_as_integers( void * data_a, void * data_b ) {
    long int a = (long int) data_a;
    long int b = (long int) data_b;

    if ( a < b ) {
        return -1;
    }
    if ( a == b ) {
        return 0;
    }
    return 1;
}
