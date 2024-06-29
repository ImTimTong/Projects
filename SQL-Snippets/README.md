# SQL Snippets 

## [View Code](https://github.com/ImTimTong/Projects/tree/main/SQL-Snippets)

## Overview
The following SQL Data Definition Language (DDL) statements are part of a larger MySQL project focused on developing a Twitter-like application from Database Lab. These statements define the database schema necessary for storing user information and chirp data (equivalent to tweets). Only the DDL statements required to execute the ParrotStatistics view are included. This view enables analysis of chirping behavior among users of the application.

### DDL Statements
1. User_ Table
  - Contains information about users.
  - Attributes include tag (username), email, password, address details, and signup date.
  - Primary key is the user's tag.

2. Bird Table
  - Contains information about users who are birds (the regular users of the app, as opposed to advertisers).
  - Inherits attributes from the User_ table and adds additional attributes like income, bird's birthdate, and gender.
  - Primary key is also the tag, which is a foreign key referencing the User_ table.
  - Note: In MySQL, foreign keys are automatically indexed by default, so there's no need for explicit indexing. However, indexing is crucial for optimizing performance, especially in scenarios like joins.

3. Chirp Table
  - Represents the posts (tweets) made by users.
  - Attributes include tag (username of the user who posted), chirp number, location coordinates, text, date, and time.
  - Primary key is a composite key consisting of tag and chirp number.
  - Contains a foreign key constraint referencing the Bird table (tag), indicating the user who posted the chirp.
  - Also contains a foreign key constraint referencing a parent post (parent_tag and parent_cno), in the case that the chirp is a repost (or parrot) of an original post.

### ParrotStatistics View
Includes the following fields:
  1. Bird tag
  2. Bird email address
  3. Bird age (calculated from birthdate)
  4. Number of chirps
  5-7. Minimum, Maximum, Average chirp sentiment
  8-9. Starting and ending date of the period when this bird was chirping
      
All birds should appear in the view, even if they haven't chirped (in which case, their chirp count would be zero).

A sample output of the ParrotStatistics view has been provided in the file "example_view_output.png" using sample data. This output illustrates the format and content of the view's results.
