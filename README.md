## About this project 

This is my attempt to build a git with its basic functionalities. Here are the rules I 
imposed to myself for this project

- The project should be built based on the information provided by the git official documentation 
    - The official git project can be checked
- It needs be unit tested
- It needs to be simple to run the project
- It need to be simple to run the unit tests

## Conventions

- Every function named with the prefix sf_ should have its return variable freed (sf stands for "should free");
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
- [x] Create tree objects interface (This will be used by the upd) 

### Index 

- [x] Read and write to index file
- [x] Add new object to index
- [x] Update index 

### Getting the project back on track

- [ ] Review the git documentation to get back the context from the project
- [ ] Review currently implemented functionality
- [ ] Setup a new roadmap

## Developer Log

#### 01-jan-2026 
So, this project has been stale for a while now 😕. The last time I touched it, I was really struggling with understanding and implementing some parts of the index, and I ended up leaving it for what I initially thought would be just a few days, but it turned into almost a year.

Today, GitHub sent me a notification related to this repo, and I thought this is an amazing opportunity to revive it entirely. There is still a lot to do in order to implement the base Git functionalities, and I think I’m better suited to tackle the problems I faced now that I’ve gained more experience.

I do, however, need to take a step back and read both the Git documentation and my own implementations to regain context for the project. Because of this, I added a new category to the roadmap called “Getting the project back on track.” Time to start again!
