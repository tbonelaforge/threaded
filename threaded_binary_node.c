#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "threaded_binary_node.h";

char * DEFAULT_DATA_PRINTER( void * data ) {
    char * return_value = malloc( ( 32 + 2 ) * sizeof( char ) );
    if ( !return_value ) {
        return NULL;
    }

    // Interpret argument as memory address.
    *return_value = '\0';
    sprintf( return_value, "%p", data );
    return return_value;
}

struct threaded_binary_node * new_threaded_binary_node() {
    struct threaded_binary_node * result = malloc( sizeof( struct threaded_binary_node ) );
    if ( !result ) {
        return NULL;
    }
    result->left_link = NULL;
    result->right_link = NULL;
    result->threaded = 'n';
    result->data = NULL;
    result->height = 1;
    return result;
}

struct threaded_binary_node * new_threaded_binary_head() {
    struct threaded_binary_node * head = new_threaded_binary_node();
    head->right_link = head;
    head->left_link = head;
    head->threaded = 'l';
    return head;
}

struct threaded_binary_node * insert_left_leaf( struct threaded_binary_node * node, struct threaded_binary_node * child ) {
    child->left_link = node->left_link;
    node->left_link = child;
    child->right_link = node;
    child->threaded = 'b';
    if ( node->right_link == node ||
         node->threaded == 'l' ) { // The given node was the head of an empty tree.
        node->threaded = 'n';
    } else { // The given node was a leaf with threaded == 'b'
        node->threaded = 'r';
    }
    return child;
}

struct threaded_binary_node * insert_right_leaf( struct threaded_binary_node * node, struct threaded_binary_node * child ) {
    child->right_link = node->right_link;
    node->right_link = child;
    child->left_link = node;
    child->threaded = 'b';
    if ( node->threaded == 'b' ) {
        node->threaded = 'l';
    } else { // node was only right-threaded
        node->threaded = 'n';
    }
    return child;
}

char * print_threaded_tree( struct threaded_binary_node * self, ptr2dataprinter data_printer ) {
    if ( !data_printer ) {
        data_printer = &DEFAULT_DATA_PRINTER;
    }
    char * left_string = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    int left_string_was_allocated = 0;
    char * right_string = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
    int right_string_was_allocated = 0;
    char * data_string = "";
    int data_string_was_allocated = 0;
    char * template = 
        "<table border='1'>"
            "<tr align='center'>"
                "<td colspan='2'>address : %p<br />data : %s<br />left_link: %p<br />right_link : %p<br />threaded : %c<br />height : %d</td>"
            "</tr>"
            "<tr align='center'>"
                "<td>%s</td>"
                "<td>%s</td>"
            "</tr>"
        "</table>";
    int template_length = 512;
    char * result_string;
    int result_string_length;
    struct threaded_binary_node * child;
    if ( child = get_threaded_left_child( self ) ) {
        left_string = print_threaded_tree( child, data_printer );
        left_string_was_allocated = 1;
    }
    if ( child = get_threaded_right_child( self ) ) {
        if ( child != self ) {
            right_string = print_threaded_tree( child, data_printer );
            right_string_was_allocated = 1;
        }
    } 
    if ( data_string = (*data_printer)( self->data ) ) {
        data_string_was_allocated = 1;        
    } else {
        data_string = "";
    }
    result_string_length = template_length 
        + strlen( left_string )
        + strlen( right_string ) 
        + strlen( data_string ) 
        + 75; // The 75 is for all the memory addresses.

    result_string = malloc( ( result_string_length + 1 ) * sizeof( char ) );
    if ( !result_string ) {
        return NULL;
    }
    *result_string = '\0';
    sprintf( result_string, template, 
             self, 
             data_string, 
             self->left_link, 
             self->right_link, 
             self->threaded, 
             self->height, 
             left_string,
             right_string
    );
   if ( left_string_was_allocated ) {
       free( left_string );
   }
   if ( right_string_was_allocated ) {
       free( right_string );
   }
   if ( data_string_was_allocated ) {
       free( data_string );
   }
    return result_string;
    
}



struct threaded_binary_node * get_threaded_left_child( struct threaded_binary_node * self ) {
    if ( self->threaded == 'l' || self->threaded == 'b' ) {
        return NULL;
    }
    return self->left_link;
}

struct threaded_binary_node * get_threaded_right_child( struct threaded_binary_node * self ) {
    if ( is_threaded_head( self ) ) {
        return NULL;
    }
    if ( self->threaded == 'r' || self->threaded == 'b' ) {
        return NULL;
    }
    return self->right_link;
}

struct threaded_binary_node * get_threaded_parent( struct threaded_binary_node * self ) {
    struct threaded_binary_node * leaf;
    struct threaded_binary_node * parent;

    if ( is_threaded_head(self) ) {
        return NULL;
    }

    // First guess that self is a right child.
    leaf = get_leftmost_threaded_descendent( self );
    parent = get_threaded_predecessor( leaf );
    if ( parent->right_link == self ) {
        return parent;
    }

    // Otherwise, self must be a left child.
    leaf = get_rightmost_threaded_descendent( self );
    parent = get_threaded_successor( leaf );
    return parent;
    
}

struct threaded_binary_node * get_threaded_successor( struct threaded_binary_node * node ) {
    if ( node->threaded == 'r' || node->threaded == 'b' ) {
        return node->right_link;
    }
    return get_leftmost_threaded_descendent( node->right_link );
}

struct threaded_binary_node * get_threaded_predecessor( struct threaded_binary_node * node ) {
    if ( node->threaded == 'l' || node->threaded == 'b' ) {
        return node->left_link;
    }
    return get_rightmost_threaded_descendent( node->left_link );
}

struct threaded_binary_node * get_leftmost_threaded_descendent( struct threaded_binary_node * node ) {
    struct threaded_binary_node * child;

    while ( child = get_threaded_left_child( node ) ) {
        node = child;
    }
    return node;
}

struct threaded_binary_node * get_rightmost_threaded_descendent( struct threaded_binary_node * node ) {
    struct threaded_binary_node * child;

    while ( child = get_threaded_right_child( node ) ) {
        node = child;
    }
    return node;
}

int is_threaded_left_child( struct threaded_binary_node * self ) {
    struct threaded_binary_node * parent = get_threaded_parent( self );
    if ( parent->left_link == self ) {
        return 1;
    }
    return 0;
}

int is_threaded_right_child( struct threaded_binary_node * self ) {
    struct threaded_binary_node * parent = get_threaded_parent( self );
    if ( parent->right_link == self ) {
        return 1;
    }
    return 0;
}

void delete_right_leaf( struct threaded_binary_node * leaf ) {
    struct threaded_binary_node * parent = get_threaded_parent( leaf );
    parent->right_link = get_threaded_successor( leaf );
    if ( parent->threaded == 'l' ) {
        parent->threaded = 'b';
    } else { // The parent has threaded = 'n'
        parent->threaded = 'r';
    }
    free( leaf );
    return;
}

void delete_left_leaf( struct threaded_binary_node * leaf ) {
    struct threaded_binary_node * parent = get_threaded_parent( leaf );
    parent->left_link = get_threaded_predecessor( leaf );
    if ( parent->threaded == 'r' ) {
        parent->threaded = 'b';
    } else { // The parent has threaded = 'n'
        parent->threaded = 'l';
    }
    free( leaf );
    return;
}

void delete_leaf( struct threaded_binary_node * leaf ) {
    if ( is_threaded_left_child( leaf ) ) {
        delete_left_leaf( leaf );
    } else {
        delete_right_leaf( leaf );
    }
    return;
}

int has_right_thread( struct threaded_binary_node * p ) {
    if ( p->threaded == 'r' || p->threaded == 'b' ) {
        return 1;
    }
    return 0;
}

int has_left_thread( struct threaded_binary_node * p ) {
    if ( p->threaded == 'l' || p->threaded == 'b' ) {
        return 1;
    }
    return 0;
}

void add_left_threaded_status( struct threaded_binary_node * p ) {
    if ( p->threaded == 'n' ) {
        p->threaded = 'l';
    } else if ( p->threaded == 'r' ) {
        p->threaded = 'b';
    }
    return;
}

void add_right_threaded_status( struct threaded_binary_node * p ) {
    if ( p->threaded == 'n' ) {
        p->threaded = 'r';
    } else if ( p->threaded == 'l' ) {
        p->threaded = 'b';
    }
    return;
}

void replace_child( struct threaded_binary_node * old_child, struct threaded_binary_node * parent, struct threaded_binary_node * new_child ) {
    if ( old_child == get_threaded_left_child( parent ) ) {
        parent->left_link = new_child;
    } else if ( old_child == get_threaded_right_child( parent ) ) {
        parent->right_link = new_child;
    }
    return;
}

void remove_right_threaded_status( struct threaded_binary_node * p ) {
    if ( p->threaded == 'b' ) {
        p->threaded = 'l';
    } else if ( p->threaded == 'r' ) {
        p->threaded = 'n';
    }
    return;
}

void remove_left_threaded_status( struct threaded_binary_node * p ) {
    if ( p->threaded == 'b' ) {
        p->threaded = 'r';
    } else if ( p->threaded == 'l' ) {
        p->threaded = 'n';
    }
    return;
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
    calculate_threaded_height( pivot );
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
    calculate_threaded_height( pivot );
}

struct threaded_binary_node * threaded_search( struct threaded_binary_node * p, void * target, ptr2comparator comparator ) {
    struct threaded_binary_node * previous = NULL;
    int comparison = -1;

    while ( p ) {
        previous = p;
        if ( !p->data ) {
            p = get_threaded_left_child( p );
            continue;
        }
        comparison = (*comparator)( target, p->data );
        if ( comparison == 0 ) {
            break;
        }
        if ( comparison == -1 ) {
            p = get_threaded_left_child( p );
        } else {
            p = get_threaded_right_child( p );
        }
    }
    return previous;
}

struct threaded_binary_node * threaded_insert( struct threaded_binary_node * root, void * value, ptr2comparator comparator ) {
    struct threaded_binary_node * new_node = NULL;
    int comparison = -1;
    struct threaded_binary_node * search_result = threaded_search( root, value, comparator );
    if ( search_result->data ) {
        comparison = (*comparator)( value, search_result->data );
    }
    if ( comparison == 0 ) { // Already exists.
        return search_result;
    }
    new_node = new_threaded_binary_node();
    new_node->data = value;
    if ( comparison == -1 ) { // Less than t's value.
        insert_left_leaf( search_result, new_node );
    } else { // Greater than t's value.
        insert_right_leaf( search_result, new_node );
    }
    calculate_threaded_height( search_result );
    return new_node;
}

int max_height( int left_height, int right_height ) {
    return ( left_height > right_height ) ? left_height : right_height;
}



void calculate_threaded_height( struct threaded_binary_node * self ) {
    struct threaded_binary_node * left_child = get_threaded_left_child( self );
    struct threaded_binary_node * right_child = get_threaded_right_child( self );
    struct threaded_binary_node * parent = NULL;
    int left_child_height = ( left_child ) ? left_child->height : 0;
    int right_child_height = ( right_child ) ? right_child->height : 0;
    self->height = 1 + max_height( left_child_height, right_child_height );
    if ( parent = get_threaded_parent( self ) ) {
        calculate_threaded_height( parent );
    }
}

int is_threaded_head( struct threaded_binary_node * node ) {
    if ( !node->data ) {
        return 1;
    }
    return 0;
}


void fix_imbalance( struct threaded_binary_node * self ) {
    int heavy_child_index;
    int other_child_index;
 
    struct threaded_binary_node * heavy_child = NULL;
    struct threaded_binary_node * other_child = NULL;
    struct threaded_binary_node * outer_grandchild = NULL;
    struct threaded_binary_node * inner_grandchild = NULL;

    // Find heavy child.
    heavy_child_index = get_heavy_child_index( self );
    heavy_child = get_threaded_child( self, heavy_child_index );
    if ( !( get_threaded_height( heavy_child ) >= 2 ) ) { // There is no imbalance here.
        return;
    }
    other_child_index = ( heavy_child_index + 1 ) % 2;
    other_child = get_threaded_child( self, other_child_index );
    outer_grandchild = get_threaded_child( heavy_child, heavy_child_index );
    inner_grandchild = get_threaded_child( heavy_child, other_child_index );
    if ( get_threaded_height( inner_grandchild ) > get_threaded_height( outer_grandchild ) ) {

        // Turn inner imbalance into outer imbalance.
        rotate( heavy_child, heavy_child_index ); 
    }

    // We have an outer imbalance.
    rotate( self, other_child_index );
}




void balance( struct threaded_binary_node * self ) {
    struct threaded_binary_node * original_parent = NULL;

    if ( is_threaded_head( self ) ) {
        return;
    }
    original_parent = get_threaded_parent( self );
    if ( !is_balanced( self ) ) {
        fix_imbalance( self );
    }
    balance( original_parent );
}

struct threaded_binary_node * get_threaded_child( struct threaded_binary_node * self, int child_index ) {
    if ( child_index == 1 ) {
        return get_threaded_right_child( self );
    } else {
        return get_threaded_left_child( self );
    }
}

void rotate( struct threaded_binary_node * pivot, int direction ) {
    if ( direction == 1 ) {
        rotate_right( pivot );
    } else {
        rotate_left( pivot );
    }
}

int is_balanced( struct threaded_binary_node * self ) {
    int left_child_height = get_threaded_child_height( self, 0 );
    int right_child_height = get_threaded_child_height( self, 1 );

    if ( abs( left_child_height - right_child_height ) >= 2 ) { // out of wack.
        return 0;
    }
    return 1;
}

int get_threaded_child_height( struct threaded_binary_node * self, int index ) {
    struct threaded_binary_node * child = NULL;

    if ( index == 1 ) {
        child = get_threaded_right_child( self );
        return ( child ) ? child->height : 0;
    } else {
        child = get_threaded_left_child( self );
        return ( child ) ? child->height : 0;
    }
}

int get_threaded_height( struct threaded_binary_node * self ) {
    if ( !self ) {
        return 0;
    }
    return self->height;
}

int get_heavy_child_index( struct threaded_binary_node * self ) {
    struct threaded_binary_node * this_child = NULL;
    struct threaded_binary_node * other_child = NULL;
    int i;
    
    for ( i = 0; i < 2; i++ ) {
        this_child = get_threaded_child( self, i );
        other_child = get_threaded_child( self, ( i + 1 ) % 2 );
        if ( get_threaded_height( this_child ) >= get_threaded_height( other_child ) ) {
            return i;
        }
    }
}


struct threaded_binary_node * insert( struct threaded_binary_node * self, void * value, ptr2comparator comparator ) {
    struct threaded_binary_node * new_node = threaded_insert( self, value, comparator );
    balance( new_node );
    return new_node;
}
