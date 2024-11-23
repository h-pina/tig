

## About this project 

This is my attempt to build a git with its basic functionalities. Here are the rules I 
imposed to myself for this project

- The project should be built based on the information provided by the git official documentation 
    - The official git project can be checked
- It needs be unit tested
- It needs to be simple to run the project
- It need to be simple to run the unit tests

## Conventions

- Every function named with the prefix sf_ should have its return variable freed;
- All errors and exceptions stop the code execution, returning 1. Since this is a learning project, I`m more
interested in understanding what is breaking the code than to build a reliable tool (Altough 
implementing reliability can be a fun thing in the future)

## Roadmap 

### Project Setup
- [x] Setup build system for building project and running unit tests

### Blob objects
- [x] Create first iteration of "git hash-object" --> parse arguments and return hash
- [x] Create init first iteration --> build obj database 
- [x] store hashed object inside object database
- [x] Improve test cases for current implemented functions
- [x] Think a way to test the fs acess
    - Solution: There is a function named _setTigFolderName_ inside the fs.c file. It allows the test functions to define a custom name for the folder. The idea is that the program will use the new folder name as the .tig folder, so the tests can run all the functions as needed. However, I`m not sure if it is completely working like this

### Tree objects
- [x] Create tree objects interface

### Commit objects
- [ ] Create commit objects interface
- [ ] Implement git config --user.name and user.email
- [ ] Implement commit message logic

--> Maybe a checkpoint to change projects a bit ?

### Index and cache-tree
> At this stage, the interfaces are already complete, now
> we need to implement the add-commit process

- [ ] Create the index file at *init* command
- [ ] add antries to the index using the *tig update-index --add* command
    - Also point to the user that the --add flag should be used it the index does not already have an entry
- [ ] add antries to the index using the *tig update-index* command
- [ ] build the cache tree at first commit
- [ ] Create invalidate logic for staged files
- [ ] Create new tree objects from cache-tree




