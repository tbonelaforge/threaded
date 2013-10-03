#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "threaded_binary_node.h";
#include "treap.h";

struct threaded_binary_node * new_threaded_binary_node() {
    struct threaded_binary_node * result = malloc( sizeof( struct threaded_binary_node ) );
    if ( !result ) {
        return NULL;
    }
    result->left_link = NULL;
    result->right_link = NULL;
    result->threaded = 'n';
    result->data = NULL;
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

char * print_threaded_tree( struct threaded_binary_node * self ) {
    char * left_string = "";
    char * right_string = "";
    char * template = 
        "<table border='1'>"
            "<tr align='center'>"
                "<td colspan='2'>address : %p<br />value : %c<br />left_link: %p<br />right_link : %p<br />threaded : %c<br />priority : %d</td>"
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
        left_string = print_threaded_tree( child );
    }
    if ( child = get_threaded_right_child( self ) ) {
        if ( child != self ) {
            right_string = print_threaded_tree( child );
        }
    }
    
    result_string_length = template_length + strlen( left_string ) + strlen( right_string ) + 32;
    result_string = malloc( ( result_string_length + 1 ) * sizeof( char ) );
    *result_string = '\0';
    struct treap_data * data = self->data;
    sprintf( result_string, template, self, ( data ) ? data->value : ' ', self->left_link, self->right_link, self->threaded, ( data ) ? data->priority : 0, left_string, right_string );
    return result_string;
    
}



struct threaded_binary_node * get_threaded_left_child( struct threaded_binary_node * self ) {
    if ( self->threaded == 'l' || self->threaded == 'b' ) {
        return NULL;
    }
    return self->left_link;
}

struct threaded_binary_node * get_threaded_right_child( struct threaded_binary_node * self ) {
    if ( self->threaded == 'r' || self->threaded == 'b' ) {
        return NULL;
    }
    return self->right_link;
}

struct threaded_binary_node * get_threaded_parent( struct threaded_binary_node * self ) {
    struct threaded_binary_node * leaf;
    struct threaded_binary_node * parent;

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
