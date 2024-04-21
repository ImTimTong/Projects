# Spreadsheet 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/Spreadsheet)

## Description
This program is a spreadsheet. An entry stores the first and last name of a person along with their age. It manages three linked lists representing different age groups (<=18, >=65, and between). It provides functions for checking duplicates, inserting new entries, listing all entries, listing entries by age, and removing specific entries. The program also includes an auto-save feature that saves the current state of the lists to a file every 15 seconds. Thread safety is ensured using mutex locks.

## Usage
The program is run from the command line with three arguments: the name of the data file, the name of the auto-save file, and the encryption key. For example:
```bash
./a.out data.txt autosave.txt 5
```
or run `make` to use makefile, which compiles program and runs it.

Encryption key integer may be limited to 128-255 due to ASCII Code conversions from XOR.

Once the program is running, the user can enter commands to interact with the linked lists:
- '1' followed by a first name, last name, and age to insert a new entry. For example: 1 John Doe 25
- '2' to list all entries. Note that different entries with the same full name (first and last) aren't allowed.
- '3' followed by an age to list all entries with that age. For example: 3 2
- '4' followed by a first name and last name to remove an entry. For example: 4 John Doe
- '5' to read the auto-save file.
- '0' to quit the program and save the data to the data file.


## Compatibility Note
Program is compatible with macOS. To be compatible with Linux:

- Remove comments for `stdio_ext.h` and `__fpurge`
- Delete `fpurge`
