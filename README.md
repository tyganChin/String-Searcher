# String-Searcher
#### Main Author : Tygan Chin
- ##### Sub-Authors : Tufts CS Adim, Emily Ye
#### Language : C
#### Date : April 18, 2023



## Description
Indexes the strings in the files of a given directory and takes in user queries to search for 
the strings case sensitive and insensitively and stores the output in a user provided output 
file. 
*Similar to the Linux Program Grep


## Architecture

- **main.cpp** - Runs the Gerp program

    - **Gerp** - Indexes the strings in the given directory and responds to user queries
                 regarding them (instances of strings)
  
        - **fileHash**  -  A hash of filenames and their relative paths

        - **WordHash** - A hash of Word objects 
          
            - **Word**  - Represents the instances of a string and it's different cases
                          within the given directory (contains locations of the words).
