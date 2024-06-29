# Deque 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/Deque)

## Overview
This project implements a list data structure (`list.c`) with stack, queue, and index operations. The list stores elements of a generic datatype and uses a linked list with each node containing a circular queue array. The `list.c` file provides functions for creating and destroying the list, counting items in the list, adding and removing items from the start and end of the list, as well as getting and setting items at a given index in the list.

## Usage
To compile the programs, navigate to the project directory in your terminal and run the following command:

```bash
make clean all
```
This command will clean any existing compiled files, compile all the programs (maze, radix, and qsort), and create executable files for each.

## Implementation Details
`list.c`: Implements the list data structure with the following functions:
  - `createList()`: Creates a circular doubly linked list with a sentinel node.
  - `destroyList()`: Frees all memory allocated for the list.
  - `numItems()`: Returns the number of items in the list.
  - `addFirst()`, `addLast()`: Adds an item to the start or end of the list.
  - `removeFirst()`, `removeLast()`: Removes and returns the first or last item in the list.
  - `getItem()`, `setItem()`: Gets or sets an item at a given index in the list.
  - `getFirst()`, `getLast()`: Returns the first or last item in the list.
    
## Testing
The functionality of the list implementation was tested by integrating it into provided `maze.c`, `qsort.c`, and `radix.c` programs (not authored by me).

`maze.c`: Implements maze generation and solving using the curses library. It uses functions from `list.c` to manage a stack data structure required for maze traversal.

`qsort.c`: Reads words from a text file and stores them in a list. It then sorts the words using the quicksort algorithm. The implementation uses functions from `list.c` to manage the list data structure.

`radix.c`: Reads a sequence of non-negative integers from standard input and sorts them using radix sort. The implementation uses a list data structure to manage buckets, as required by the radix sort algorithm.
