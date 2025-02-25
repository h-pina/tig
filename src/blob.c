#include "object.h"
#include "blob.h"
#include "logger.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define READBUFSIZE 1024

//TODO: Fix the size limitation of 1024 characters
void readContent(char* contentBuffer, HashObjArgs opts){
	if(opts.useStdin){
		log_dbg("Reading from content to be hashed from stdin");
		ssize_t bytesRead = read(STDIN_FILENO, contentBuffer, READBUFSIZE);
		contentBuffer[bytesRead] = '\0';
	}
	else if(strcmp(opts.filename, "") != 0){
		log_dbg("Reading from file %s", opts.filename);
		FILE* fp = fopen(opts.filename, "r");
		fgets(contentBuffer, 1024, fp);	//read from file
	}
	else{
		log_err("No content was supplied for hashing, exiting...");
		exit(EXIT_FAILURE);
	}
}

void hashObjCmd(HashObjArgs ho, char* hashBuffer){
	char contentBuffer[READBUFSIZE] = { 0 };// must be filled with for consistent hashing
	readContent(contentBuffer, ho);
	log_dbg("Content to hash: %s", contentBuffer); 
	char* content = sf_addHeaderToContent(contentBuffer, "blob");
	char* hash = sf_hashObject(content); 
	if(ho.write){
		saveToObjDb(hash, content);
	}
	strcpy(hashBuffer, hash);
	free(content);
	free(hash);
}
