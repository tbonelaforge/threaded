#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "threaded_binary_node.h"

/*============================================================
Data printer to be used during testing 
============================================================*/
char * print_data_as_integer( void * );

/*============================================================

Comparator to be used when searching and inserting.

============================================================*/

int compare_data_as_integers( void *, void * );

/*============================================================

Wrapper around print function for this test.

============================================================*/

void testprint( struct threaded_binary_node * );

/*============================================================

Wrapper around threaded insert function for this test.

============================================================*/

struct threaded_binary_node * testinsert( struct threaded_binary_node *, int );


/*============================================================

Wrapper around balanced insert function for this test.

============================================================*/

struct threaded_binary_node * testbalancedinsert( struct threaded_binary_node *, int );

/*============================================================

Wrapper around search function for this test.

============================================================*/

struct threaded_binary_node * testsearch( struct threaded_binary_node *, int );

/*============================================================

Testing routine for inserts

============================================================*/
struct threaded_binary_node * test_three_inserts( int, int, int );


void print_header( char * info ) {
    printf( "<hr />\n" );
    printf( "============================================================<br />\n" );
    printf( "%s<br />\n", info );
    printf( "============================================================<br />\n" );
}


/*============================================================

Main testing routine.

============================================================*/

void test_basic_threading_functions();
void test_inserts_and_rotations();
void test_balancing();
void test_balancing_inserts();

int main() {

    test_basic_threading_functions();
    test_inserts_and_rotations();
    test_balancing();
    test_balancing_inserts();

}


void test_basic_threading_functions() {
    printf( "<hr />\n" );
    printf( "============================================================<br />\n" );
    printf( "Testing basic tree construction, and successor and predecessor functions<br />\n" );
    printf( "============================================================<br />\n" );

    struct threaded_binary_node * head = new_threaded_binary_head();
    struct threaded_binary_node * node1 = new_threaded_binary_node();
    node1->data = (void *)(long int) 42;
    insert_left_leaf( head, node1 );
    printf( "After adding the first element, the tree looks like:\n<br />" );
    testprint( head );

    struct threaded_binary_node * node2 = new_threaded_binary_node();
    node2->data = (void *)(long int) 43;
    insert_left_leaf( node1, node2 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    testprint( head );

    struct threaded_binary_node * node3 = new_threaded_binary_node();
    node3->data = (void *)(long int) 44;
    insert_right_leaf( node1, node3 );
    printf( "After adding the second element, the tree looks like:\n<br />" );
    testprint( head );

    struct threaded_binary_node * successor;

    printf( "The successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( node2 );
    testprint( successor );

    printf( "The second successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    testprint( successor );

    printf( "The third successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    testprint( successor );


    printf( "The fourth successor of node2 ( 43 ) is:<br />\n" );
    successor = get_threaded_successor( successor );
    testprint( successor );


    struct threaded_binary_node * predecessor;

    printf( "The predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( node3 );
    testprint( predecessor );

    printf( "The second predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    testprint( predecessor );

    printf( "The third predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    testprint( predecessor );


    printf( "The fourth predecessor of node3 ( 44 ) is:<br />\n" );
    predecessor = get_threaded_predecessor( predecessor );
    testprint( predecessor );

}


void test_inserts_and_rotations() {
    printf( "<hr />\n" );
    printf( "============================================================<br />\n" );
    printf( "Testing threaded inserts, and rotation functions<br />\n" );
    printf( "============================================================<br />\n" );

    struct threaded_binary_node * post_insert;

    printf( "About to test the insertion of 42, 43, and 44\n" );
    post_insert = test_three_inserts( 42, 43, 44 );

    printf( "About to rotate left about 42:<br />\n" );
    rotate_left( testsearch( post_insert, 42 ) );
    testprint( post_insert );

    printf( "About to test the insertion of 42, 44, and 43\n" );
    post_insert = test_three_inserts( 42, 44, 43 );
    
    printf( "About to rotate left about 42:<br />\n" );
    rotate_left( testsearch( post_insert, 42 ) );
    testprint( post_insert );

    printf( "About to test the insertion of 43, 42, and 44\n" );
    post_insert = test_three_inserts( 43, 42, 44 );

    printf( "About to rotate left about 43:<br />\n" );
    rotate_left( testsearch( post_insert, 43 ) );
    testprint( post_insert );

    printf( "About to test the insertion of 43, 44, and 42\n" );
    post_insert = test_three_inserts( 43, 44, 42 );

    printf( "About to rotate right about 43:<br />\n" );
    rotate_right( testsearch( post_insert, 43 ) );
    testprint( post_insert );

    printf( "About to test the insertion of 44, 42, and 43\n" );
    post_insert = test_three_inserts( 44, 42, 43 );

    printf( "About to rotate right about 44:<br />\n" );
    rotate_right( testsearch( post_insert, 44 ) );
    testprint( post_insert );

    printf( "About to test the insertion of 44, 43, and 42\n" );
    post_insert = test_three_inserts( 44, 43, 42 );

    printf( "About to rotate right about 44:<br />\n" );
    rotate_right( testsearch( post_insert, 44 ) );
    testprint( post_insert );
}

void test_balancing() {
    printf( "<hr />\n" );
    printf( "============================================================<br />\n" );
    printf( "Testing balancing inserts, and rotation functions<br />\n" );
    printf( "============================================================<br />\n" );

    struct threaded_binary_node * head = new_threaded_binary_head();
    struct threaded_binary_node * target = NULL;

    testinsert( head, 42 );
    target = testinsert( head, 43 );
    testinsert( head, 44 );
    
    printf( "before balancing, the tree looks like:\n" );
    testprint( head );

    printf( "About to balance (from the result of inserting 43:<br />\n" );
    balance( target );
    printf( "The balancing is done.<br />\n" );
    printf( "After balancing, the head looks like:<br />\n" );
    testprint( head );
    printf( "============================================================<br />\n" );

    printf( "before balancing, the tree looks like: \n" );
    head = new_threaded_binary_head(); // Throw away memory!
    target = testinsert( head, 42 );
    testinsert( head, 43 );
    testinsert( head, 44 );
    testprint( head );

    printf( "About to balance (from the result of inserting 42):<br />\n" );
    balance( target );
    printf( "The balancing is done, now the head looks like:<br />\n" );
    testprint( head );
    printf( "============================================================<br />\n" );

    printf( "before balancing, the tree looks like: <br />\n" );
    head = new_threaded_binary_head(); // Throw away some more memory!
    target = testinsert( head, 40 );
    testinsert( head, 30 );
    testinsert( head, 50 );

    testinsert( head, 55 );
    testinsert( head, 45 );
    target = testinsert( head, 42 );
    testprint( head );

    printf( "About to balance ( from the result of inserting 42):<br />\n" );
    balance( target );
    printf( "The balancing is done, now the head looks like:<br />\n" );
    testprint( head );
    printf( "============================================================<br />\n" );

    printf( "before balancing, the tree looks like: <br />\n" );
    head = new_threaded_binary_head(); // Throw away some more memory!
    target = testinsert( head, 40 );
    testinsert( head, 30 );
    testinsert( head, 50 );

    testinsert( head, 55 );
    testinsert( head, 45 );
    target = testinsert( head, 47 );
    testprint( head );

    printf( "About to balance ( from the result of inserting 47):<br />\n" );
    balance( target );
    printf( "The balancing is done, now the head looks like:<br />\n" );
    testprint( head );
    printf( "============================================================<br />\n" );
    
    
    
}

void test_balancing_inserts() {
    struct threaded_binary_node * head;
    print_header( "Testing balancing after inserts" );
    printf( "After inserting 42, 43, 44, 45, 46, 47, and 48, the tree looks like:<br />\n" );
    head = new_threaded_binary_head();
    testbalancedinsert( head, 42 );
    testbalancedinsert( head, 43 );
    testbalancedinsert( head, 44 );
    testbalancedinsert( head, 45 );
    testbalancedinsert( head, 46 );
    testbalancedinsert( head, 47 );
    testbalancedinsert( head, 48 );
    testprint( head );
    
    
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



struct threaded_binary_node * test_three_inserts( int a, int b, int c ) {
    struct threaded_binary_node * head = new_threaded_binary_head();

    testinsert( head, a );
    printf( "After inserting %d, the tree looks like: <br />\n", a );
    testprint( head );

    testinsert( head, b );
    printf( "After inserting %d, the tree looks like: <br />\n", b );
    testprint( head );

    testinsert( head, c );
    printf( "After inserting %d, the tree looks like: <br />\n", c );
    testprint( head );
    return head;
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


void testprint( struct threaded_binary_node * node ) {
    printf( "%s<br />\n", print_threaded_tree( node, &print_data_as_integer ) );
}

struct threaded_binary_node * testinsert( struct threaded_binary_node * head, int value ) {
    return threaded_insert( head, (void *) (long int) value, &compare_data_as_integers );
}

struct threaded_binary_node * testbalancedinsert( struct threaded_binary_node * head, int value ) {
    return insert( head, (void *) (long int) value, &compare_data_as_integers );
}

struct threaded_binary_node * testsearch( struct threaded_binary_node * root, int target ) {
    return threaded_search( root, (void *) (long int) target, &compare_data_as_integers );
}
