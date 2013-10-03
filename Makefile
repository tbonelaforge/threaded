all: threaded_binary_node.o threaded_binary_node_test

threaded_binary_node.o: threaded_binary_node.c threaded_binary_node.h
	gcc -c threaded_binary_node.c -o threaded_binary_node.o

threaded_binary_node_test: threaded_binary_node_test.c threaded_binary_node.h threaded_binary_node.o
	gcc threaded_binary_node_test.c threaded_binary_node.o -o threaded_binary_node_test