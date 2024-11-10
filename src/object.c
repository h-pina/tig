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
		contentBuffer[bytesRead] = '\0';
	}
}


char* sf_hashObject(const char* content, HashObjArgs opts){
	log_dbg("Hashing object...");

	//TODO: enable \0 in content
	log_war("Current hash_object function cannot handle files with \\0 inside"
				 " its content");
	int contentLen = strlen(content); 
	char* contentBuff = malloc(contentLen + 20); //some space for the header
	if(contentBuff == NULL){
		log_err(
			"Out of memory. Malloc could not allocate %d bytes", contentLen+20
		);
		exit(EXIT_FAILURE);
	}

	//TODO: Make this logic more elegant
	char header[20];
	sprintf(header, "blob %d ", contentLen); //Last char will be replaced for \0
	int headerLen = strlen(header);
	strcat(contentBuff, header);
	strcat(contentBuff, content);
	contentBuff[headerLen-1] = '\0'; //Replace header last char for \0
	
	int contentBuffLen = headerLen + contentLen + 1;
	unsigned char hash[SHA_DIGEST_LENGTH];
	log_war(
		"The function SHA1 is not being correctly used, this may cause "
		"a segfault"
	);
	SHA1((unsigned char*)contentBuff, contentBuffLen, hash);
	free(contentBuff);
	
	char* resultBuff = calloc(SHA_DIGEST_LENGTH*2+1, sizeof(char));
	if(resultBuff == NULL){
		log_err(
			"Out of memory. Malloc could not allocate %d bytes", SHA_DIGEST_LENGTH+1
		);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf(resultBuff + 2*i,"%02x", hash[i]); 
	}
	resultBuff[SHA_DIGEST_LENGTH*2] = '\0';
	return resultBuff;
}

void saveToObjDb(const char* hash, const char* content){
	log_dbg("Saving object to obj db...");
	/*
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

	
	free(splittedHash);*/
}	

void hashObjCmd(HashObjArgs ho){
	char contentBuffer[READBUFSIZE] = { 0 };
	readContent(contentBuffer, ho.useStdin);
	log_dbg("Content read: %s", contentBuffer);
	char* hash = sf_hashObject(contentBuffer, ho);
	printf("%s\n", hash);
	if(ho.write){
		saveToObjDb(hash, contentBuffer);
	}
	free(hash);
}
