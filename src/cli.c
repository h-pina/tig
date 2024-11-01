#include "cli.h"
#include "object.h"
#include <bits/getopt_core.h>
#include <unistd.h>

void parseCliCommand(char** argv, int argc){
	//First --> process Only hash-obj command
	HashObjOpts ho = {.write = 0, .useStdin = 0};
	char c;
	while((c = getopt(argc, argv, "ws")) != -1){
		switch(c){
			case 'w':
				ho.write = 1;
				break;
			case 's':
				ho.useStdin = 1;
				break;
		}
	}
	hashObjCmd(ho);
}

