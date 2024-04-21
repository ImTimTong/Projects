// Filename: list.c
// Author: Timothy Tong
// Description: This program manages three linked lists representing different age groups. It provides functions for checking duplicates, inserting new entries, listing all entries, listing entries by age, and removing specific entries. Thread safety is ensured using mutex locks.

#include "link.h"

// This function checks if a name is duplicated in any of the three linked lists. It locks the mutex before checking each list and unlocks it afterwards. If a duplicate is found, it sets a flag and breaks the loop.
int check_duplicate(char temp_full[40])
{
  char real_full[40];
  int flag = 0;
  NODE *p;
  int i;

  // iterate over three linked lists
  for (i = 0; i < 3; i++)
  {
    // lock mutex, no other threads can access the linked list during duplicate check
    pthread_mutex_lock(&mutex);
    p = threelists[i].head;
    while (p != NULL)
    {
      // for each node in list get full name and compare with input
      strcpy(real_full, p->info.first_name);
      strcat(real_full, p->info.last_name);
      if (strcmp(temp_full, real_full) == 0)
      {
        printf("Duplicate name\n");
        flag = 1;
        break;
      }
      p = p->next;
    }
    // unlock mutex so other threads can modify the linked list
    pthread_mutex_unlock(&mutex);

    // stop iterating if found duplicate
    if (flag == 1)
    {
      break;
    }
  }
  // flag is 1 if is dupicate 0 if not
  return flag;
}

// This function inserts a new node into the appropriate linked list based on the age. It locks the mutex before inserting the node and unlocks it afterwards.
void insert(char *temp_first, char *temp_last, int temp_age)
{
  // allocates memory for a new node
  NODE *p = (NODE *)malloc(sizeof(NODE));
  if (p == NULL)
  {
    printf("No memory available\n");
    return;
  }
  // put name and age into Person info struct of the new node
  strcpy(p->info.first_name, temp_first);
  strcpy(p->info.last_name, temp_last);
  p->info.age = temp_age;

  // currently last node in last
  p->next = NULL;

  // put node in corresponding linked list based on age
  // less than or equal to 18, sets i to 0 (first linked list)
  int i;
  if (temp_age <= 18)
  {
    i = 0;
  }

  // greater than or equal to 65, sets i to 2 (third linked list)
  else if (temp_age >= 65)
  {
    i = 2;
  }

  // Otherwise, sets i to 1 (second linked list)
  else
  {
    i = 1;
  }

  // locks the mutex to ensure that no other thread can modify the linked list while this function is inserting the new node
  pthread_mutex_lock(&mutex);

  // if the linked list is empty, sets the head and tail to the new node
  if (threelists[i].tail == NULL)
  {
    p->prev = NULL;
    threelists[i].tail = p;
    threelists[i].head = threelists[i].tail;
  }

  // list is not empty
  else
  {
    // add new node to end of list and make as new tail
    threelists[i].tail->next = p;
    p->prev = threelists[i].tail;
    threelists[i].tail = p;
  }
  // unlocks the mutex, allowing other threads to modify the linked list
  pthread_mutex_unlock(&mutex);
  return;
}

// This function prints out all the entries in the three linked lists. It locks the mutex before accessing each list and unlocks it afterwards.
void list(void)
{
  int entries = 0;
  NODE *p;
  int i;

  // iterate over the three linked lists
  for (i = 0; i < 3; i++)
  {
    // locks the mutex to ensure that no other thread can modify the linked list while this function is printing the entries
    pthread_mutex_lock(&mutex);
    p = threelists[i].head;

    // print name and age for each node in linked list
    while (p != NULL)
    {
      printf("%s %s %d\n", p->info.first_name, p->info.last_name, p->info.age);
      p = p->next;
      entries++;
    }
    // unlocks the mutex, allowing other threads to modify the linked list.
    pthread_mutex_unlock(&mutex);
  }
  if (entries == 0)
  {
    printf("No entries\n");
  }
  return;
}

// This function prints out all the entries of a specific age in the appropriate linked list. It locks the mutex before accessing the list and unlocks it afterwards.
void list_age(void)
{
  int entries = 0;

  // get and store age from user
  int wanted_age;
  if (scanf("%d", &wanted_age) != 1)
  {
    printf("Need age\n");
    return;
  }
  NODE *p;
  // locks the mutex to ensure that no other thread can modify the linked list while this function is operating
  pthread_mutex_lock(&mutex);

  // Determine which linked list to search through based on the age
  // If age is less than or equal to 18, sets p to the head of the first linked list
  if (wanted_age <= 18)
  {
    p = threelists[0].head;
  }

  // If the age is greater than or equal to 65, sets p to the head of the third linked list
  else if (wanted_age >= 65)
  {
    p = threelists[2].head;
  }

  // Otherwise, sets p to the head of the second linked list
  else
  {
    p = threelists[1].head;
  }

  // go through linked list and print the person full name if found an age match
  while (p != NULL)
  {
    if (p->info.age == wanted_age)
    {
      printf("%s %s\n", p->info.first_name, p->info.last_name);
      entries++;
    }
    p = p->next;
  }

  // unlocks the mutex, allowing other threads to modify the linked list
  pthread_mutex_unlock(&mutex);
  if (entries == 0)
  {
    printf("No entry for this age\n");
  }
  return;
}

// This function removes an entry with a specific name from the appropriate linked list. It locks the mutex before accessing each list and unlocks it afterwards. If the entry is not found, it prints a message.
void remove_entry(char first_name[], char last_name[])
{
  // store full name of person to be removed
  char temp_full[40];
  strcpy(temp_full, first_name);
  strcat(temp_full, last_name);
  NODE *p, *q;
  int i;

  // iterate through three linked lists
  for (i = 0; i < 3; i++)
  {
    // locks the mutex to ensure that no other thread can modify the linked list while this function is operating
    pthread_mutex_lock(&mutex);
    p = threelists[i].head;
    while (p != NULL)
    {
      // for each node, get the full name of that person and compare with the target full name
      char real_full[40];
      strcpy(real_full, p->info.first_name);
      strcat(real_full, p->info.last_name);

      // if there's a match, remove the node, deal with different cases:
      if (strcmp(temp_full, real_full) == 0)
      {
        // if it's the only node in the list
        if (threelists[i].tail == threelists[i].head)
        {
          threelists[i].tail = NULL;
          threelists[i].head = NULL;
        }

        // if the node is the head
        else if (p == threelists[i].head)
        {
          // make next node the head
          threelists[i].head = threelists[i].head->next;
        }

        // if the node is the tail
        else if (p == threelists[i].tail)
        {
          // make second to last node the tail
          threelists[i].tail = q;
          threelists[i].tail->next = NULL;
        }

        // if node is in the middle of the list
        else
        {
          q->next = p->next;
        }

        // deallocate node memory
        free(p);

        // unlocks the mutex, allowing other threads to modify the linked list
        pthread_mutex_unlock(&mutex);
        return;
      }
      // each time p is moved to the next node, q is set to the previous node
      q = p;
      p = p->next;
    }
    // unlocks the mutex, allowing other threads to modify the linked list
    pthread_mutex_unlock(&mutex);
  }

  // if reaches this point, haven't returned, name not in lists
  printf("Name not found\n");
  return;
}
