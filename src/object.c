#include "object.h"
#include "utils/utils.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>

#define READBUFSIZE 1024

void readContent(char* contentBuffer, int useStdin){
	if(useStdin){
		ssize_t bytesRead = read(STDIN_FILENO, contentBuffer, READBUFSIZE);

		//Just as a precaution. If the input already has \0, there will be \0\0 at the end
		contentBuffer[bytesRead+1] = '\0'; 
	}
}


void hashObject(const char* content, HashObjArgs opts, char* resultBuff){
	log_dbg("Hashing object...");

	//TODO: enable \0 in content
	log_war("Current hash_object function cannot handle files with \0 inside\
				 its content");
	int contentLen = strlen(content); 
	char* contentBuff = malloc(contentLen + 20); //some space for the header
	if(contentBuff == NULL){
		log_err(
			"Out of memory. Malloc could not allocate %d bytes", contentLen+20
		);
		exit(EXIT_FAILURE);
	}

	char header[20];
	sprintf(header, "blob %d ", contentLen); //Last char will be replaced for \0
	int headerLen = strlen(header);
	strcat(contentBuff, header);
	strcat(contentBuff, content);
	contentBuff[headerLen-1] = '\0'; //replace header last char for \0
	
	int contentBuffLen = headerLen + contentLen + 1;
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1((unsigned char*)contentBuff, contentBuffLen-1, hash);
	free(contentBuff);
	
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf(resultBuff + 2*i,"%02x", hash[i]); 
	}
}

void saveToObjDb(const char* hash, const char* content){
	log_dbg("Saving object to obj db...");
	char** splittedHash = sf_splitString(hash, 1);
	char folderPath[100], filePath[100];

	sprintf(folderPath, "./.tig/objects/%s", splittedHash[0]);
	printf("%s",folderPath);
	mkdir(folderPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	printf("%s",splittedHash[1]);
	sprintf(filePath, "%s/%s", folderPath, splittedHash[1]);
	printf("%s",filePath);
	FILE* fptr = fopen(filePath, "r");
	fputs(content, fptr);

	
	free(splittedHash);
}	

void hashObjCmd(HashObjArgs ho){
	char contentBuffer[READBUFSIZE] = { 0 };
	readContent(contentBuffer, ho.useStdin);
	char resultBuffer[RESULT_BUFFER_LENGTH] = { 0 };
	hashObject(contentBuffer, ho, resultBuffer);
	printf("%s\n", resultBuffer);
	if(ho.write){
		saveToObjDb(resultBuffer, contentBuffer);
	}
}
