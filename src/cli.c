#include "object.h"
#include "init.h"
#include "logger.h"

#include <bits/getopt_core.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

//TODO: Error for cases where invalid options
//TODO: Add help option
HashObjArgs parseHashObjArgs(char** argv, int argc){
	optind = 1;
	HashObjArgs ho = {.write = 0, .useStdin = 0, .filename = ""};
	int c;        
	int option_index = 0;
	static struct option long_options[] = {
            {"usestdin",no_argument,0,0},
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
loggerInit(debug);

if(argc == 1){
	printHelpMsg();
	return;
}

//Function pointers tuples(commands, parseArgsFn), and
//parseCliFunction is just a switch basically
if(strcmp(argv[1], "hash-object") == 0){
	log_dbg("Launching hash-object command");
	hashObjCmd(parseHashObjArgs(argv, argc));
}
else if(strcmp(argv[1], "init") == 0){
		log_dbg("Init command identified, launching init() function");
		init();
		return;
	}
	else{
		printHelpMsg();
	}
}

