# To-Do List Manager 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/To-Do-List-Manager)

## Overview
The To-Do List Manager provides a comprehensive solution for managing tasks efficiently. With the ToDoList class, users can seamlessly add, remove, prioritize tasks, and even save or load tasks from YAML files. Additionally, a helper function is available to parse JSON strings effortlessly.

## Usage
The `ToDoList` class can be run as a standalone program from the terminal by executing the following command:
```bash
ruby ToDoList.rb
```

This will initiate the To-Do List Manager, allowing users to interact with various functionalities via a menu interface:
  - Press 'a' to add tasks
  - Press 'c' to reorder tasks
  - Press 'r' to delete tasks
  - Press 'v' to view tasks
  - Press 'q' to quit the program

Messages are color-coded for better readability:
  - Blue for task list
  - Green for success messages
  - Red for warnings
  - Yellow for load/save operations
  - White for general program information

Additional Features:
  - Tasks are unique to ensure clarity and prevent duplication.
  - Users can add tasks via array input or single-item input (string or numeric).
  - When providing an array input, ensure to use double quotes for strings within the array to add each item individually. Otherwise, the entire array will be considered as a single input.

Alternatively, you can integrate the ToDoList class into other Ruby scripts by requiring the file and instantiating the class. The following ensures that the start method of the ToDoList class is executed only when the script is run as the main program directly from the terminal:

```ruby
require_relative 'ToDoList'

if __FILE__ == $PROGRAM_NAME
  todolist = ToDoList.new
  todolist.start
end
```
