#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>

void readContent(const char* contentBuffer, int useStdin){

}

void hashObject(const char* content, HashObjArgs opts, char* resultBuff){
	//First iteration: Add header without null byte at the end of header
	//TODO: Change this to a custom function. If the file contains a \0 
	// 			there might be a problem
	int contentLen = strlen(content); 
	char* strBuffer = malloc(contentLen + 20); //some space for the header
	char header[20];

	sprintf(header, "blob %d ", contentLen); //Last char will be replaced for \0
	int headerLen = strlen(header);

	strcat(strBuffer, header);
	strcat(strBuffer, content);

	strBuffer[headerLen-1] = '\0'; //replace header last char for \0
	int strBufferLen = headerLen + contentLen + 1;
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1((unsigned char*)strBuffer, strBufferLen-1, hash);

	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf(resultBuff + 2*i,"%02x", hash[i]); 
	}

}

void saveToObjDb(const char* hash, const char* content){

	

}

void hashObjCmd(HashObjArgs ho){ }
