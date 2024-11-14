

### About this project 

This is my attempt to build a git with its basic functionalities. Here are the rules I 
imposed to myself for this project

- The project should be built based on the information provided by the git official documentation 
    - The official git project can be checked
- It needs be unit tested
- It needs to be simple to run the project
- It need to be simple to run the unit tests

### Conventions

- Every function named with the prefix sf_ should have its return variable freed;
- All errors and exceptions stop the code execution, returning 1. Since this is a learning project, I`m more
interested in understanding what is breaking the code than to build a reliable tool (Altough 
implementing reliability can be a fun thing in the future)

### Roadmap 
- [x] Setup build system for building project and run unit tests
- [x] Create first iteration of "git hash-object" --> parse arguments and return hash
- [x] Create init first iteration --> build obj database 
- [x] store hashed object inside object database
- [x] Create a logger class
- [ ] Improve tests and increase coverage (not looking for a specific number, but a lot of functions are untested)
- [ ] Consider create a separate file for blob objects, since 'objects' is a general term inside git architecture
- [ ] Create tree objects
- [ ] Create index


