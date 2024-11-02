#include "object.h"
#include <bits/getopt_core.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>

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
		//Create validation for filenames
		strcpy(ho.filename,argv[argc-1]);
	}
	return ho;
}

void parseCliCommand(char** argv, int argc){
	//Function pointers tuples(commands, parseArgsFn), and
	//parseCliFunction is just a switch basically
	hashObjCmd(parseHashObjArgs(argv, argc));
}

