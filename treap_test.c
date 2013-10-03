#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treap.h"

int main() {
    /*
    printf( "ABout to construct a tree for the purposes of testing the search function.\n" );
    struct threaded_binary_node * root = new_threaded_binary_head();
    struct threaded_binary_node * node1 = new_threaded_binary_node();
    struct treap_data * data1 = new_treap_data();
    data1->value = 'g';
    data1->priority = 1;
    node1->data = (void *) data1;
    insert_left_leaf( root, node1 );

    struct threaded_binary_node * node2 = new_threaded_binary_node();
    struct treap_data * data2 = new_treap_data();
    data2->value = 'c';
    data2->priority = 2;
    node2->data = (void *) data2;
    insert_left_leaf( node1, node2 );

    struct threaded_binary_node * node3 = new_threaded_binary_node();
    struct treap_data * data3 = new_treap_data();
    data3->value = 'k';
    data3->priority = 2;
    node3->data = (void *) data3;
    insert_right_leaf( node1, node3 );

    struct threaded_binary_node * node4 = new_threaded_binary_node();
    struct treap_data * data4 = new_treap_data();
    data4->value = 'a';
    data4->priority = 2;
    node4->data = data4;
    insert_left_leaf( node2, node4 );

    struct threaded_binary_node * node5 = new_threaded_binary_node();
    struct treap_data * data5 = new_treap_data();
    data5->value = 'e';
    data5->priority = 2;
    node5->data = data5;
    insert_right_leaf( node2, node5 );

    struct threaded_binary_node * node6 = new_threaded_binary_node();
    struct treap_data * data6 = new_treap_data();
    data6->value = 'i';
    data6->priority = 2;
    node6->data = data6;
    insert_left_leaf( node3, node6 );

    struct threaded_binary_node * node7 = new_threaded_binary_node();
    struct treap_data * data7 = new_treap_data();
    data7->value = 'm';
    data7->priority = 2;
    node7->data = data7;
    insert_right_leaf( node3, node7 );

    printf( "The tree to be used for testing the search function is:<br />\n" );
    printf( "%s<br />\n", print_threaded_tree( root ) );


    // Perform a variety of searches.
    struct threaded_binary_node * result;
    printf( "The result of searching for 'g' is:<br />\n" );
    result = search( root, 'g' );
    printf( "%s<br />\n", print_threaded_tree( result ) );

    printf( "The result of searching for 'f' is:<br />\n" );
    result = search( root, 'f' );
    printf( "%s<br />\n", print_threaded_tree( result ) );
    
    printf( "The result of searching for 'a' is:<br />\n" );
    result = search( root, 'a' );
    printf( "%s<br />\n", print_threaded_tree( result ) );


    // Use the just-built tree to test some rotations.
    rotate_right( node1 );
    printf( "After rotating right, the tree looks like:<br />\n" );
    printf( "%s<br />\n", print_threaded_tree( root ) );

    rotate_right( node1 );
    printf( "After rotating right again, the tree looks like:<br />\n" );
    printf( "%s<br />\n", print_threaded_tree( root ) );

    printf( "After rotating left, the tree looks like:<br />\n" );
    rotate_left( node1 );
    printf( "%s<br />\n", print_threaded_tree( root ) );

    printf( "After rotating left again, the tree looks like:<br />\n" );
    rotate_left( node1 );
    printf( "%s<br />\n", print_threaded_tree( root ) );

    printf( "AFter performing a series of rotations, the tree lookslike:<br />\n" );
    perform_rotations( node1 );
    printf( "%s<br />\n", print_threaded_tree( root ) );


    // Try inserting into the tree.
    printf( "After inserting a new l into the tree, the tree looks like:<br />\n" );
    insert( root, 'l' );
    printf( "%s<br />\n", print_threaded_tree( root ) );
*/

/*
    // Try inserting into a brand new tree...
    struct threaded_binary_node * new_tree = new_threaded_binary_head();
printf("INside treap_test, about to insert into a brand new tree!<br />\n" );
    insert( new_tree, 'a' );
printf( "Inside treap_test, just got done inserting into a brand-new tree!<br />\n" );
printf( "It looks like: <br />\n" );
printf( "%s<br />\n", print_threaded_tree( new_tree ) );

printf("INside treap_test, about to insert again.");
    insert( new_tree, 'b' );
printf( "Inside treap_test, just got done inserting into a brand-new tree!<br />\n" );

printf( "It looks like: <br />\n" );
printf( "%s<br />\n", print_threaded_tree( new_tree ) );


    insert( new_tree, 'b' );
printf( "Inside treap_test, just got done inserting into a brand-new tree!<br />\n" );
printf( "It looks like: <br />\n" );
printf( "%s<br />\n", print_threaded_tree( new_tree ) );

    insert( new_tree, 'x' );
printf( "Inside treap_test, just got done inserting into a brand-new tree!<br />\n" );
printf( "It looks like: <br />\n" );
printf( "%s<br />\n", print_threaded_tree( new_tree ) );

    insert( new_tree, 'a' );
    printf( "After inserting a,b,b,x,a into a brand new treap, it looks like:<br />\n" );
    printf( "%s<br />\n", print_threaded_tree( new_tree ) );

    insert( new_tree, 'y' );
    printf( "After inserting a,b,b,x,a,y into a brand new treap, it looks like:<br />\n" );
    printf( "%s<br />\n", print_threaded_tree( new_tree ) );
*/

//    char * string = "ajkjhgfrqqppookmbczhkytrwwsjmmllpimngcvcraqresxrj,ppoo";
    char * string = "ammweoqweoerujncnchhaoheoiqoiewnfnadndfnlaloiciobcohansdndafslneooidfioafsndfasndsoiohbyqoyeqwoenam;.xz.x.adf.nfnanbnoabpoweqopernnwanaiuugftgdhbnnbqnibqiqijenndigibbtbatbbabndaeriuiiufnnnzppqbqnbqiuucnbnapbpadfae";
    printf( "Going to locate the first non-repeating character in:\n%s\n", string );
    int len = strlen( string );
    struct threaded_binary_node * new_tree = new_threaded_binary_head();
    int i;
    for ( i = 0; i < len; i++ ) {
        char c = string[i];
        insert( new_tree, c );
    }
    struct threaded_binary_node * result_node = get_threaded_left_child( new_tree );
    struct treap_data * result_data = result_node->data;
    char result = result_data->value;
    printf( "The first non-repeating character is: \n%c\n", result );

}

