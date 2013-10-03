#include <stdlib.h>
#include <stdio.h>
#include "threaded_binary_node.h"

#include "treap.h"

struct treap_data * new_treap_data() {
    struct treap_data * new_data = malloc( sizeof( struct treap_data ) );
    if ( !new_data ) {
        return NULL;
    }
    new_data->value = '\0';
    new_data->priority = 0;
    return new_data;
}

struct threaded_binary_node * search( struct threaded_binary_node * p, char value ) {
    struct treap_data * target_data = new_treap_data();
    target_data->value = value;
    struct threaded_binary_node * previous = NULL;
    int comparison;
    while ( p ) {
        comparison = compare( target_data, p->data );
        if ( comparison == 0 ) {
            previous = p;
            break;
        }
        previous = p;
        if ( comparison == -1 ) {
            p = get_threaded_left_child( p );
        } else {
            p = get_threaded_right_child( p );
        }
    }
    free( target_data );
    return previous;
}


int compare( struct treap_data * data1, struct treap_data * data2 ) {
    if ( !data2 || ( data1->value < data2->value ) ) {
        return -1;
    }
    if ( data1->value > data2->value ) {
        return 1;
    }
    return 0;
}

void rotate_right( struct threaded_binary_node * pivot ) {
    struct threaded_binary_node * child = get_threaded_left_child( pivot );
    struct threaded_binary_node * parent = get_threaded_parent( pivot );
    if ( has_right_thread( child ) ) {
        pivot->left_link = child;
        add_left_threaded_status( pivot );
        remove_right_threaded_status( child );
    } else {
        pivot->left_link = child->right_link;
    }
    child->right_link = pivot;
    replace_child( pivot, parent, child );
}

void rotate_left( struct threaded_binary_node * pivot ) {
    struct threaded_binary_node * child = get_threaded_right_child( pivot );
    struct threaded_binary_node * parent = get_threaded_parent( pivot );
    if ( has_left_thread( child ) ) {
        pivot->right_link = child;
        add_right_threaded_status( pivot );
        remove_left_threaded_status( child );
    } else {
        pivot->right_link = child->left_link;
    }
    child->left_link = pivot;
    replace_child( pivot, parent, child );
}

void perform_rotations( struct threaded_binary_node * t ) {
    struct threaded_binary_node * parent = get_threaded_parent( t );
    if ( !is_dominated( t, parent ) ) { // Rotate t "up"
        if ( parent->left_link == t ) {
            rotate_right( parent );
        } else { // The given node was a right child.
            rotate_left( parent );
        }
        perform_rotations( t );
        return;
    }
    struct threaded_binary_node * highest_priority_child = get_highest_priority_child( t );
    if ( !highest_priority_child ) {
        return;
    }
    if ( !is_dominated( highest_priority_child, t ) ) {
        if ( t->left_link == highest_priority_child ) {
            rotate_right( t );
        } else { // The highest priority child is t's right child.
            rotate_left( t );
        }
        perform_rotations( t );
    }
    return;
}

int is_dominated( struct threaded_binary_node * child, struct threaded_binary_node * parent ) {
    if ( !parent->data ) {
        return 1;
    }
    struct treap_data * parent_data = parent->data;
    struct treap_data * child_data = child->data;
    if ( parent_data->priority <= child_data->priority ) {
        return 1;
    }
    return 0;
}

struct threaded_binary_node * get_highest_priority_child( struct threaded_binary_node * parent ) {
    struct threaded_binary_node * highest_priority_child = NULL;
    int highest_priority;
    struct threaded_binary_node * child = NULL;
    struct treap_data * child_data = NULL;
    if ( ( child = get_threaded_left_child( parent ) ) ) {
        highest_priority_child = child;
        child_data = child->data;
        highest_priority = child_data->priority;
    }
    if ( ( child = get_threaded_right_child( parent ) ) ) {
        child_data = child->data;
        if ( child_data->priority < highest_priority ) {
            highest_priority_child = child;
            highest_priority = child_data->priority;
        }
    }
    return highest_priority_child;
}

struct threaded_binary_node * insert( struct threaded_binary_node * root, char c ) {
    struct treap_data * target_data = new_treap_data();
    target_data->value = c;
    target_data->priority = 1; // Assume c will not be found.
    int comparison = -1;

    struct threaded_binary_node * t = search( root, c );
    if ( t->data ) {
        struct treap_data * my_treap_data = t->data;
        comparison = compare( target_data, my_treap_data );
    } 
    if ( comparison == 0 ) { // Duplicate character.
        struct treap_data * t_data = t->data;
        t_data->priority++;
        free( target_data );
    } else { // Need to insert
        struct threaded_binary_node * new_node = new_threaded_binary_node();
        new_node->data = (void *)target_data;
        if ( comparison == -1 ) {
            t = insert_left_leaf( t, new_node );
        } else { // The comparison was +1 ( insert right )
            t = insert_right_leaf( t, new_node );
        }
    }
    perform_rotations( t );
    return t;
}
