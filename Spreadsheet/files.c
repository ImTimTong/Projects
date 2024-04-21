// Filename: files.c
// Author: Timothy Tong
// Description: Contains functions for reading and writing data to and from files in both text and binary formats. It handles XOR encryption/decryption for text files and manages linked lists for storing and manipulating data. It also includes thread-safe operations using mutex locks to prevent data races in multithreaded contexts.

#include "link.h"

// This function reads data from a file specified by filename. The data is XOR-decrypted using the key, then parsed into first name, last name, and age, and inserted into the linked list.
void read_data(char *filename, int key)
{
  FILE *infp;
  if ((infp = fopen(filename, "r")) == NULL)
  {
    printf("File does not exist\n");
  }
  else
  {
    char temp[45];
    while (fgets(temp, 45, infp) != NULL)
    {
      // Decrypt the data in-place
      char *q = temp;
      while (*q != '\n')
      {
        *q ^= key;
        q++;
      }
      char first_name[20], last_name[20];
      int age;
      // Put data into variables and insert into list
      sscanf(temp, "%s%s%d", first_name, last_name, &age);
      insert(first_name, last_name, age);
    }
    fclose(infp);
  }
  return;
}

// This function writes the data from the linked list to a file specified by filename. Before writing, the data is XOR-encrypted using the key. The function also deletes the nodes from the list after writing their data to the file.
void save_data(char *filename, int key)
{
  FILE *outfp;
  if ((outfp = fopen(filename, "w")) == NULL)
  {
    printf("File cannot be opened, data not saved\n");
    return;
  }
  else
  {
    // iterate over the three linked lists array defined in main.c
    int i;
    for (i = 0; i < 3; i++)
    {
      // lock the mutex to ensure no other thread can modify the linked list as it's saved to the file
      pthread_mutex_lock(&mutex);
      NODE *p = threelists[i].head;
      while (p != NULL)
      {
        // get name and age from each node into a string
        char temp[45];
        sprintf(temp, "%s %s %d\n", p->info.first_name, p->info.last_name, p->info.age);

        // encrypt the data
        char *q = temp;
        while (*q != '\n')
        {
          *q ^= key;
          q++;
        }

        // write to file
        fprintf(outfp, "%s", temp);
        p = p->next;
      }

      // delete linked list and free memory after processing all nodes
      delete_nodes(threelists[i].head);

      // unlock the mutex to allow other threads access
      pthread_mutex_unlock(&mutex);
    }
    fclose(outfp);
  }
  return;
}

// This function recursively deletes nodes from the linked list, starting from the node pointed to by p.
void delete_nodes(NODE *p)
{
  // base case
  if (p == NULL)
  {
    return;
  }
  delete_nodes(p->next);
  free(p);
  return;
}

// This function periodically writes the data from the linked list to a binary file specified by bfname. The data is written in binary format without any encryption. The function runs in an infinite loop, writing to the file every 15 seconds.
void *auto_save(void *bfname)
{
  FILE *boutfp;
  while (1)
  {
    // lock mutex, no other thread can modify linked lists during save
    pthread_mutex_lock(&mutex);

    // open file in write binary mode
    if ((boutfp = fopen((char *)bfname, "wb")) == NULL)
    {
      printf("Binary file cannot be opened, data not saved\n");
      pthread_mutex_unlock(&mutex);
      return NULL;
    }

    // iterate over three linked lists array from main.c
    int i;
    for (i = 0; i < 3; i++)
    {
      NODE *p = threelists[i].head;
      while (p != NULL)
      {
        // write each node as binary data to file
        fwrite(p, sizeof(NODE), 1, boutfp);
        p = p->next;
      }
    }
    fclose(boutfp);
    // unlock so other threads can access linked lists
    pthread_mutex_unlock(&mutex);

    // repeat save every 15 seconds
    sleep(15);
  }
  return NULL;
}

// This function reads data from a binary file specified by bfname and prints it to the console. The data is read in binary format without any decryption.
void read_auto(char *bfname)
{
  FILE *binfp;

  // lock mutex to prevent other threads from modifying file during read
  pthread_mutex_lock(&mutex);

  // open file in read binary mode
  if ((binfp = fopen(bfname, "rb")) == NULL)
  {
    printf("File does not exist\n");
  }
  else
  {
    NODE temp[10];
    int i, r;
    int entries = 0;

    // read up to 10 nodes at a time; loop runs until no more nodes to read
    while ((r = fread(temp, sizeof(NODE), 10, binfp)) > 0)
    {
      // print each node's name + age to console
      for (i = 0; i < r; i++)
      {
        printf("%s %s %d\n", temp[i].info.first_name, temp[i].info.last_name, temp[i].info.age);
        entries++;
      }
    }
    if (entries == 0)
    {
      printf("No entries\n");
    }
    fclose(binfp);
  }

  // unlock mutex so other threads can access file
  pthread_mutex_unlock(&mutex);
  return;
}
