#include "blob.h"
#include "tree.h"
#include "index.h"
#include "init.h"
#include "logger.h"
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//TODO: Test Functions, delete later
void createFile(const char* filename){
	FILE* fp = fopen(filename, "w");
	fclose(fp);
}

void removeFile(const char* filename){
	remove(filename);
}

//TODO: Error for cases where invalid options
//TODO: Add help option
HashObjArgs parseHashObjArgs(char** argv, int argc){
	optind = 1;
	HashObjArgs ho = {.write = 0, .useStdin = 0, .filename = ""};
	int c;        
	int option_index = 0;
	static struct option long_options[] = {
            {"stdin",no_argument,0,0},
            {0,0,0,0 }
	};

	while(
		(c = getopt_long(argc, argv, "w",long_options, &option_index)) != -1
	){
		switch(c){ 
			case 0:
				ho.useStdin = 1;
				break;
			case 'w':
				ho.write = 1;
				break;
		}
	}

	if(!ho.useStdin){
		//TODO: Create validation for filenames
		strcpy(ho.filename,argv[argc-1]);
	}
	return ho;
}

void printHelpMsg(){
	printf(
		"\033[1mTig - A git clone for learning\033[0m \n"
		"usage: tig [init | hash-object]\n"
		"Currently available subcommands:\n"
		" init          initializes tig folder\n"
		" hash-object   hashes the selected file for the object database\n"
	);
}

void parseCliCommand(char** argv, int argc){
	loggerInit(error);

	if(argc == 1){
		printHelpMsg();
	}

	//Function pointers tuples(commands, parseArgsFn), and
	//parseCliFunction is just a switch basically
	if(strcmp(argv[1], "hash-object") == 0){
		log_dbg("Launching hash-object command");
		char hashBuffer[41];
		hashObjCmd(parseHashObjArgs(argv, argc), hashBuffer);
		log_dbg("%s", hashBuffer);
		log_dbg("hash-object command finished");
	}
	else if(strcmp(argv[1], "init") == 0){
		log_dbg("init command identified, launching init() function");
		init();
	} 
	else if(strcmp(argv[1], "test_tree") == 0){
		struct TreeObjEntry entries[2];
		struct TreeObjEntry e1 = {
			.hash = "a906cb2a4a904a152e80877d4088654daad0c859",
			.mode = 100644,
			.path = "README",
			.type = "blob",
		};
		entries[0] = e1;
		struct TreeObjEntry e2 = {
			.hash = "a906cb2a4a904a152e80877d4088654daad0c859",
			.mode = 040000,
			.path = "lib",
			.type = "tree",
		};
		entries[1] = e2;
		createTreeObj(entries, 2);
	} 
	else if(strcmp(argv[1], "test_index_fs") == 0){

		struct IndexEntry* entries =  malloc(2*sizeof(struct IndexEntry));
		entries[0] = (struct IndexEntry){
			.path = "/test/path/1",
			.hash = "03f5e78eb21"
		};
		entries[1] = (struct IndexEntry){
			.path = "/test/path/2",
			.hash = "03f5e78eb12312a5"
		};
		struct Index i = {
			.numEntries = 2,
			.entries = entries
		};

		log_dbg("Calling index writing function..");
		writeToIndexFile(&i);


		log_dbg("Reading from index");
		struct Index retrievedI;
		readFromIndexFile(&retrievedI);
		log_dbg("Test Complete!");
		
	} 
	else if(strcmp(argv[1], "test_index_fs") == 0){

		struct IndexEntry* entries =  malloc(2*sizeof(struct IndexEntry));
		entries[0] = (struct IndexEntry){
			.path = "/test/path/1",
			.hash = "03f5e78eb21"
		};
		entries[1] = (struct IndexEntry){
			.path = "/test/path/2",
			.hash = "03f5e78eb12312a5"
		};
		struct Index i = {
			.numEntries = 2,
			.entries = entries
		};

		log_dbg("Calling index writing function..");
		writeToIndexFile(&i);


		log_dbg("Reading from index");
		struct Index retrievedI;
		readFromIndexFile(&retrievedI);
		log_dbg("Test Complete!");
		
	} 
	else if(strcmp(argv[1], "test_index_add") == 0){
		struct IndexEntry* entries =  malloc(sizeof(struct IndexEntry));
		struct Index i = {
			.numEntries = 1,
			.entries = entries
		};
		addFileToIndex(&i, "03f5e78eb12312a5", "src/test1", 01, 02);
		addFileToIndex(&i, "03ffffffffffffff", "src/test2", 132, 2789);
		printIndexEntries(&i);
	} 
	else if(strcmp(argv[1], "test_index_update") == 0){
		struct IndexEntry* entries =  malloc(sizeof(struct IndexEntry));
		struct Index i = {
			.numEntries = 1,
			.entries = entries
		};
		
		addFileToIndex(&i, "04f5e78eb12312a5", "test1", 01, 02);
		addFileToIndex(&i, "03ffffffffffffff", "test2", 132, 2789);
		createFile("test1");
		createFile("test2");
		log_dbg("Mocked index entries:");
		printIndexEntries(&i);
		updateFullIndex(&i); 
		log_dbg("Index entries after update:");
		printIndexEntries(&i);
		removeFile("test1");
		removeFile("test2");
	} 
	else{
		printHelpMsg();
	}
}
