all: threaded_binary_node.o treap.o

threaded_binary_node.o: threaded_binary_node.c threaded_binary_node.h
	gcc -c threaded_binary_node.c -o threaded_binary_node.o

treap.o: treap.c treap.h
	gcc -c treap.c -o treap.o