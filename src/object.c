#include "object.h"
#include "utils/utils.h"
#include "logger.h"
#include "fs.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#define READBUFSIZE 1024

void readContent(char* contentBuffer, int useStdin){
	if(useStdin){
		ssize_t bytesRead = read(STDIN_FILENO, contentBuffer, READBUFSIZE);
		contentBuffer[bytesRead] = '\0';
	}
	else{
		log_err("Nothing to read");
		exit(EXIT_FAILURE);
	}
}


char* sf_hashObject(const char* content, HashObjArgs opts){
	log_dbg("Hashing object...");

	//TODO: Make this construction logic more elegant
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

	char header[20];
	sprintf(header, "blob %d ", contentLen); //Last char will be replaced for \0
	int headerLen = strlen(header);

	strcat(contentBuff, header);
	strcat(contentBuff, content);
	contentBuff[headerLen-1] = '\0'; //Replace header last char for \0
	int contentBuffLen = headerLen + contentLen;
	
	//hash
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len;
	EVP_MD_CTX* hashctx =  EVP_MD_CTX_new();
	EVP_DigestInit_ex(hashctx, EVP_sha1(), NULL);
	EVP_DigestUpdate(hashctx, contentBuff, contentBuffLen);
	EVP_DigestFinal_ex(hashctx, hash, &hash_len);

	free(contentBuff);
	char* resultBuff = calloc(hash_len*2+1, sizeof(char));
	if(resultBuff == NULL){
		log_err(
			"Out of memory. Malloc could not allocate %d bytes", hash_len
		);
		exit(EXIT_FAILURE);
	}
	
	//convert hex to chars
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf(resultBuff + 2*i,"%02x", hash[i]); 
	}
	resultBuff[hash_len*2] = '\0';
	return resultBuff;
}

void saveToObjDb(char* hash, const char* content){
	log_dbg("Saving object to obj db...");
	char** splittedHash = sf_splitString(hash, 1);
	char folderPath[PATH_MAX], filePath[PATH_MAX];
	char tigPath[PATH_MAX];
	get_tig_path(tigPath);
	log_dbg("tig base path: %s",tigPath);
	sprintf(folderPath, "%s/objects/%s", tigPath,splittedHash[0]);
	log_dbg("Folder Path: %s",folderPath);
	mkdir(folderPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	sprintf(filePath, "%s/%s", folderPath, splittedHash[1]);

	log_dbg("File Path: %s",filePath);

	FILE* fptr = fopen(filePath, "w");
	if(fptr == NULL){
		log_err("Error creating file at %s.\n Error: %s", filePath, strerror(errno));
		exit(EXIT_FAILURE);
	}
	fprintf(fptr, "%s", content);
	fclose(fptr);

	/*
	free(splittedHash);
	*/
}	

void hashObjCmd(HashObjArgs ho){
	char contentBuffer[READBUFSIZE] = { 0 };// must be filled with for consistent hashing
	readContent(contentBuffer, ho.useStdin);
	log_dbg("Content read: %s", contentBuffer); char* hash = sf_hashObject(contentBuffer, ho); printf("%s\n", hash);
	if(ho.write){
		saveToObjDb(hash, contentBuffer);
	}
	free(hash);
}
