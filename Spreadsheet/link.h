// Filename: link.h
// Author: Timothy Tong
// Description: Defines structures and functions for managing a doubly-linked list of persons. It includes thread-safe operations for inserting, listing, removing, and checking duplicates. It also handles reading and saving data to files, with an auto-save feature.

#include <stdio.h>
// #include <stdio_ext.h> // for linux
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define Person struct person
#define NODE struct node
#define List struct list

struct person
{
  char first_name[20];
  char last_name[20];
  int age;
};

struct node
{
  Person info;
  NODE *next;
  NODE *prev;
};

struct list
{
  NODE *head;
  NODE *tail;
};

void insert(char *, char *, int);
void list(void);
void list_age(void);
void remove_entry(char[], char[]);
int check_duplicate(char[]);
void read_data(char *, int);
void save_data(char *, int);
void delete_nodes(NODE *);
void *auto_save(void *);
void read_auto(char *);

// Defined in main.c:

// mutex variable used to synchronize access to shared resources.
extern pthread_mutex_t mutex;

// threelists is an array of three linked lists used to store person data.
extern List threelists[3];