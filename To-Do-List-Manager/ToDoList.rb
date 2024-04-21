#!/usr/bin/env ruby

=begin
TODOLIST PROGRAM
Author: Timothy Tong

Description:
ToDoList class offers functions to add/remove tasks from list, view tasks, change task priority, load from and save to yaml file. Helper function to parse JSON string.
Start method provides menu interface for users to easily interact with different todolist instances: 'a' to add, 'c' to reorder, 'r' to delete', 'v' to view, 'q' to quit.
Different messages are color coded: blue - tasklist, green - success, red - warning, yellow - load/save, white - program info

Tasks are unique.
User can add tasks to list via array input or single item input - string or numeric.
If user inputs array, strings should use double instead of single quotes, for each item in array to be added. Otherwise, entire array registers as a single input.
=end

require 'yaml'
require 'json'

class ToDoList
  attr_reader :tasklist

  def initialize
    @tasklist = []
  end

  #Add tasks, no duplicates in tasklist 
  def add_tasks(tasks)
    begin
      raise TypeError, "\e[31m\nExpected an Array, String, or Numeric, got #{tasks.class.name}\e[0m" unless tasks.is_a?(Array) || tasks.is_a?(String) || tasks.is_a?(Numeric)
    rescue TypeError => e
      puts e.message 
      return
    end
      
    #Add array of tasks
    if tasks.is_a?(Array)
      tasks_to_add = tasks - @tasklist
      @tasklist += tasks_to_add
      if tasks_to_add.empty?
        puts "\e[31m\nNo tasks added - duplicate or empty list provided\e[0m"
        return false
      else
          puts "\e[32m\nAdded #{tasks_to_add.join(", ")}\e[0m"
          return true
      end

    #Add one task
    elsif !@tasklist.include? tasks
      @tasklist << tasks
      puts "\e[32m\nAdded #{tasks}\e[0m"
      return true

    else
      puts "\e[31m\nNo tasks added - duplicate provided\e[0m"
      return false
    end
  end

  #View tasks
  def view_tasks
    if @tasklist.empty?
      puts "\e[31m\nNo tasks in tasklist\e[0m"
      return false

    #Number and print each task
    else
      puts "\e[36m\nTASKLIST:\e[0m"
      @tasklist.each_with_index do |task, num|
        puts "\e[36m\t#{num+1}. #{task}\e[0m" 
      end
      return true
    end
  end

  #Remove tasks if in tasklist
  def rm_tasks(tasks)
    begin
      raise TypeError, "\e[31m\nExpected an Array, String, or Numeric, got #{tasks.class.name}\e[0m" unless tasks.is_a?(Array) || tasks.is_a?(String) || tasks.is_a?(Numeric)
    rescue TypeError => e
      puts e.message 
      return
    end

    #Remove tasks mentioned in array input
    if tasks.is_a?(Array)
      tasks_to_remove = tasks & @tasklist
      tasks_to_remove.each do |task|
        @tasklist.delete(task)
      end
      if tasks_to_remove.empty?
        puts "\e[31m\nNo tasks removed - not in list\e[0m"
        return false
      else
        puts "\e[32m\nRemoved #{tasks_to_remove.join(", ")}\e[0m"
        return true
      end

    #Remove one task
    elsif @tasklist.include? tasks
      @tasklist.delete(tasks)
      puts "\e[32m\nRemoved #{tasks}\e[0m" 
      return true

    else
      puts "\e[31m\nNo tasks removed - not in list\e[0m"
      return false
    end
  end

  #Changes priority of task given order number. Does nothing if not already in list. 
  def change_order(task, order)
    begin
      raise TypeError, "\e[31m\nTask must be a String or Numeric, got #{task.class.name}\e[0m" unless task.is_a?(String) || task.is_a?(Numeric)
      raise TypeError, "\e[31m\nOrder must be  an Int, got #{order.class.name}\e[0m" unless order.is_a?(Integer)
    rescue TypeError => e
      puts e.message 
      return
    end

    #New position must be within current tasklist size
    if order < 1 || order > @tasklist.length
      puts "\e[31m\nOrder must be between 1 - #{@tasklist.length}\e[0m" 
      return false
    end
    if rm_tasks(task) 
      @tasklist.insert(order-1, task)
      puts "\e[32m\nMoved #{task} to #{order}\e[0m" 
      return true
    end
    #No change if remove fails, item not already in list.
    puts "\e[31m\nDid not move #{task}\e[0m" 
    return false
  end
    
  #Load preexisting tasklist in array format from YAML
  def load_file(tasklist="tasklist.yaml")
    begin
      if File.exists?(tasklist)
        puts "\e[33m\nLoading from file #{tasklist}\e[0m"
        parsed = YAML.load(File.read(tasklist))
        #Check if valid format before loading 
        raise TypeError, "\e[31mExpected an Array got #{parsed.class.name}\e[0m" unless parsed.is_a?(Array)
        @tasklist = parsed
        puts "\e[33mLoad successful\e[0m"
        return true
      else
        puts "\e[31m\nFile does not exist. Creating new file...\e[0m" 
        file = File.open(tasklist, 'w')
        file.close
        return true
      end
    rescue => e
      puts "\e[31mError loading file: #{e.message}\e[0m"
      return false
    end
  end

  #Save tasklist in array format to YAML
  def save_file(tasklist="tasklist.yaml")
    begin
      puts "\e[33m\nSaving to file #{tasklist}\e[0m"
      File.open(tasklist, "w") {|file| file.write(@tasklist.to_yaml)}
      puts "\e[33mSave successful\e[0m"
      return true
    rescue => e
      puts "\e[31mError saving file: #{e.message}\e[0m"
      return false
    end
  end

  #Helper Function
  def JSON_parser(string) 
    begin
      #Check if string is valid JSON, return Ruby data structure 
      #Needed so array input is not interpreted as a string
      input = JSON.parse(string) 
    rescue JSON::ParserError
      #Otherwise returns unmodified input => not an array
      #Also ensure that if numeric, not passed as string type
      if string.to_i.to_s == string || string.to_f.to_s == string 
        return eval(string)
      end
      return string 
    end 
  end

  #Run Tasklist
  def start
    print "Enter file to load from (or will create new if none given): "
    #Get user input tasklist
    tasklist = gets.chomp
    #Use default file "tasklist.yaml" if none provided
    if tasklist == ""
      val = load_file  
    else
      val = load_file(tasklist)
    end
    #If invalid yaml file provided, prompt user to overwrite or stop
    if !val
      print "\e[31m\nWill overwrite #{tasklist}. Type 'y' to continue: \e[0m" 
      input = gets.chomp
      if input != "y"
        puts "\nTerminating program..."
        return
      end
      puts "\nContinuing..."
    end
    #Run loop, get user commands until quit
    loop do
      puts "\nEnter:\n\t'a' to add\n\t'c' to change order\n\t'r' to remove\n\t'v' to view\n\t'q' to quit"
      command = gets.chomp.downcase
      case command
      when 'a'
        print "Enter tasks to add (an array or single item): "
        tasks = JSON_parser(gets.chomp)
        add_tasks(tasks)
      when 'c'
        print "Enter task to move (a single item): "
        task = JSON_parser(gets.chomp)
        print "\nEnter position to move to (an integer): "
        position = JSON_parser(gets.chomp)
        change_order(task, position)
      when 'r'
        print "Enter tasks to remove (an array or single item): "
        tasks = JSON_parser(gets.chomp)
        rm_tasks(tasks)
      when 'v'
        view_tasks
      when 'q'
        if tasklist == ""
          save_file
        else 
          save_file(tasklist)
        end
        puts "\nExiting..."
        break
      else
        puts "\nInvalid command!"
      end
    end
  end
end

if __FILE__ == $PROGRAM_NAME
  todolist = ToDoList.new
  todolist.start
end
