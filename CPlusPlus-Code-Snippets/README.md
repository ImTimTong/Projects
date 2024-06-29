# C++ Snippets 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/CPlusPlus-Code-Snippets)

## Overview
These are C++ code snippets from OO Programming Lab. My partner and I collaborated on separate files for the lab assignments. The provided code snippets represent my own work, and any contributions from my partner, which are in separate files, have been omitted for clarity.

### bintree.h
This header file defines a template class binary_tree_node within the coen79_lab9 namespace. It serves as a fundamental building block for constructing binary trees in C++. The binary_tree_node class represents a node in a binary tree and provides essential functionalities for manipulating binary trees, such as accessing data, setting child pointers, and checking if a node is a leaf.

### sequence.cpp
Implements the member functions of the sequence class defined in sequence.h within the coen79_lab6 namespace. It provides functionality for working with a sequence of items stored in a forward linked list. The file includes constructors, destructor, modification member functions, and constant member functions to manage the sequence, maintaining the invariant where items are stored in sequence order. 

### deque.h
Defines a class for deque (double ended queue) within the namespace coen79_lab8. It includes template parameters, typedefs, and member constants for the deque class. The file also provides constructors, destructor, modification member functions, and constant member functions for managing the deque. Additionally, it defines standard iterator member functions for providing a forward iterator.

### deque_iterator.h
Provides a class for deque iterator (non-const) within the namespace coen79_lab8. It defines a forward iterator to step through the items of a deque. The iterator can modify the underlying deque list through the * operator. The file includes a constructor, constant member functions, and modification member functions for the iterator class. Additionally, it overloads comparison operators for iterators and provides functionality for incrementing the iterator.
