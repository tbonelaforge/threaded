#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"



int compare( void * value1, void * value2 ) {
    long int value1_int = (long int) value1;
    long int value2_int = (long int) value2;
    if ( value1_int < value2_int ) {
        return -1;
    } else if ( value1_int > value2_int ) {
        return 1;
    } else {
        return 0;
    }
}

struct heap * new_heap() {
    struct threaded_binary_node * head = new_threaded_binary_head();
    if ( !head ) {
        return NULL;
    }
    struct heap * result = malloc( 1 * sizeof(struct heap) );
    if ( !result ) {
        return NULL;
    }
    result->head = head;
    result->tail = head;
    return result;
}

int is_dominated( struct threaded_binary_node * node, struct threaded_binary_node * parent ) {
    if ( !parent->data ) {
        return 1;
    }
    if ( compare( node->data, parent->data ) > -1 ) {
        return 1;
    }
    return 0;
}

void bubble_value_up( struct threaded_binary_node * node ) {
    struct threaded_binary_node * parent = get_threaded_parent( node );

    if ( is_dominated( node, parent ) ) {
        return;
    }
    void * temp = parent->data;
    parent->data = node->data;
    node->data = temp;
    return bubble_value_up( parent );
}

struct heap * heap_insert( struct heap * this_heap, void * value ) {
    struct threaded_binary_node * new_node = new_threaded_binary_node();
    new_node->data = value;
    struct threaded_binary_node * insert_target = get_threaded_successor( this_heap->tail );

    if ( is_threaded_right_child( this_heap->tail ) || !insert_target->data ) {
        insert_target = get_threaded_successor( insert_target );
        insert_left_leaf( insert_target, new_node );
    } else {
        insert_right_leaf( insert_target, new_node );
    }
    this_heap->tail = new_node;
    bubble_value_up( new_node );
   
}

void * extract_min( struct heap * this_heap ) {
    struct threaded_binary_node * top = get_threaded_left_child(this_heap->head);
    if ( !top ) {
        return NULL;
    }
    void * result = top->data;
    top->data = this_heap->tail->data;
    struct threaded_binary_node * new_tail = get_second_predecessor(this_heap->tail);
    delete_leaf( this_heap->tail );
    this_heap->tail = new_tail;
    bubble_value_down( top );
    return result;                                              
}

void bubble_value_down( struct threaded_binary_node * node ) {
    struct threaded_binary_node * highest_priority_child = get_highest_priority_child( node );
    if ( !highest_priority_child ||
         is_dominated( highest_priority_child ) ) {
        return;
    }
    void * temp = highest_priority_child->data;
    node->data = temp;
    highest_priority_child->data = node->data;
    bubble_value_down( highest_priority_child );
}

struct threaded_binary_node * get_highest_priority_child( struct threaded_binary_node * node ) {
    struct threaded_binary_node * left_child = get_threaded_left_child( node );
    struct threaded_binary_node * right_child = get_threaded_right_child( node );
    if ( left_child && right_child && 
         compare( left_child, right_child ) > 0 ) {
        return right_child;
    }
    return left_child;
}
