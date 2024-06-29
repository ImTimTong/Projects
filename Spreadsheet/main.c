// Filename: main.c
// Author: Timothy Tong
// Description: This program is a spreadsheet. An entry stores the first and last name of a person along with their age. It manages three linked lists representing different age groups (<=18, >=65, and between). It provides functions for checking duplicates, inserting new entries, listing all entries, listing entries by age, and removing specific entries. The program also includes an auto-save feature that saves the current state of the lists to a file every 15 seconds. Thread safety is ensured using mutex locks.

// User Usage:
// The program is run from the command line with three arguments: the name of the data file, the name of the auto-save file, and the encryption key. For example:
// ./a.out data.txt autosave.txt 5
// or run make to use makefile, which compiles program and runs it.

// Once the program is running, the user can enter commands to interact with the linked lists:
// - '1' followed by a first name, last name, and age to insert a new entry. For example: 1 John Doe 25
// - '2' to list all entries. Note that different entries with the same full name (first and last) aren't allowed.
// - '3' followed by an age to list all entries with that age. For example: 3 2
// - '4' followed by a first name and last name to remove an entry. For example: 4 John Doe
// - '5' to read the auto-save file.
// - '0' to quit the program and save the data to the data file.

/*
Compatibility Note
Program is compatible with macOS. To be compatible with Linux:

- Remove comments for `stdio_ext.h` and `__fpurge`
- Delete `fpurge`
*/

#include "link.h"

// Declare mutex variable
pthread_mutex_t mutex;

// Used to store three linked lists. Each list corresponds to a different age group.
List threelists[3];

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("Need two filenames and a key\n");
    return -1;
  }

  // argv[1] is the file from which the program reads initial data and to which it finally saves data when it quits
  // argv[3] is the key for XOR encryption/decryption. Here, it's used to decrypt data read from argv[1].
  read_data(argv[1], atoi(argv[3]));

  // Initialize the mutex for thread synchronization
  pthread_mutex_init(&mutex, NULL);

  // Declare a pthread_t variable for the auto-save thread
  pthread_t thr;

  // Create a new thread that executes concurrently with the main thread for auto_save.
  // Runs in background while user continues interacting with main thread.
  // argv[2] is the file to which the program auto-saves data, which it can later read from during user interaction.
  pthread_create(&thr, NULL, auto_save, (void *)argv[2]);

  int user_input;
  while (1)
  {
    //__fpurge(stdin); // for linux
    fpurge(stdin);

    // receive user command
    if (scanf("%d", &user_input) != 1)
    {
      printf("Please enter a valid argument\n");
      continue;
    }

    // different actions based on user command
    switch (user_input)
    {

    // Cancels the auto-save thread, saves data to a file, prints "Quit", and exits the program.
    case 0:
    {
      pthread_cancel(thr);
      // Save final data to argv[1], key argv[3] used to encrypt data before saving
      save_data(argv[1], atoi(argv[3]));
      printf("Quit\n");
      return 0;
    }

    // Reads a first name, last name, and age from the user. If the input is valid and the full name isn't a duplicate, it inserts a new entry into the list.
    case 1:
    {
      char first_name[20];
      char last_name[20];
      int age;

      // Receive name (19 char each for first and last) and age for the entry
      if (scanf("%19s%19s%d", first_name, last_name, &age) != 3)
      {
        printf("%s %s %d\n", first_name, last_name, age);
        printf("Need first and last name (max: 19 char each), and age\n");
        break;
      }

      // Check if full name is a duplicate
      char temp_full[40];
      strcpy(temp_full, first_name);
      strcat(temp_full, last_name);

      // Insert if not duplicate
      if (check_duplicate(temp_full) == 0)
      {
        insert(first_name, last_name, age);
      }
      break;
    }

    // Lists all entries.
    case 2:
      list();
      break;

    // Lists all entries for a specific age.
    case 3:
      list_age();
      break;

    // Reads a full name from the user and removes the corresponding entry from the list.
    case 4:
    {
      char full_name[40];
      char first_name[20];
      char last_name[20];

      // ignore leading spaces and newline characters, and then read up to 39 characters or until a newline character is encountered
      int num = scanf("%*[ '\n']%39[^'\n']s", full_name);
      char *p = full_name;
      int count = 0;

      // get first name, up to 18 chars long
      while ((*p != ' ') && (*p != '\0') && (count < 19))
      {
        first_name[count++] = *(p++);
      }

      // if no last name
      if (*p == '\0')
      {
        printf("Need first and last name\n");
        break;
      }

      // if first name too long
      else if (*p != ' ')
      {
        printf("First name too long\n");
        break;
      }

      // null terminate
      first_name[count] = '\0';
      p++;
      count = 0;

      // repeat above to get last name
      while ((*p != ' ') && (*p != '\0') && (count < 19))
      {
        last_name[count++] = *(p++);
      }

      // got more than two words
      if (*p == ' ')
      {
        printf("Need first and last name\n");
        break;
      }

      // if not null terminated, exceeds 18 chars
      else if (*p != '\0')
      {
        printf("Last name too long\n");
        break;
      }

      // null terminate
      last_name[count] = '\0';

      // delete entry
      remove_entry(first_name, last_name);
      break;
    }

    // Reads data from the auto-save file (argv[2]).
    case 5:
      read_auto(argv[2]);
      break;

    // Prints "Invalid command" if the user input doesn't match any of the above cases.
    default:
      printf("Invalid command\n");
      break;
    }
  }
}