#include "object.h"
#include "utils/utils.h"
#include "logger.h"
#include "fs.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

char* sf_addHeaderToContent(char* content, const char* type){
	//TODO: Make this construction logic more elegant
	//TODO: enable \0 in content
	log_war("Current hash_object function cannot handle files with \\0 inside"
				 " its content");
	int contentLen = strlen(content); 

	char header[20];
	sprintf(header, "%s %d ", type ,contentLen); //Last char will be replaced for \0
	int headerLen = strlen(header);

	char* contentBuff = malloc(contentLen + 20); //some space for the header
	if(contentBuff == NULL){
		log_err(
			"Out of memory. Malloc could not allocate %d bytes", contentLen+20
		);
		exit(EXIT_FAILURE);
	}
	strcat(contentBuff, header);
	strcat(contentBuff, content);
	contentBuff[headerLen-1] = '\0'; //Replace header last char for \0

	return contentBuff;
}


char* sf_hashObject(const char* content){
	log_dbg("Hashing object...");

	int headerLen = strlen(content); 
	int contentLen = strlen(content + headerLen + 1);
	contentLen += headerLen + 1;
	log_dbg("Calculated contentLen: %d", contentLen);
	
	//hash
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len;
	EVP_MD_CTX* hashctx =  EVP_MD_CTX_new();
	EVP_DigestInit_ex(hashctx, EVP_sha1(), NULL);
	EVP_DigestUpdate(hashctx, content, contentLen);
	EVP_DigestFinal_ex(hashctx, hash, &hash_len);

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
	log_war("The saved object contents does not include the hashed header\
				  and is not deflated");
	log_dbg("Saving object to obj db...");
	char** splittedHash = sf_splitString(hash, 1);
	char folderPath[PATH_MAX], filePath[PATH_MAX];
	char tigPath[PATH_MAX];
	get_tig_path(tigPath);
	log_dbg("Identified tig base folder path: %s",tigPath);
	sprintf(folderPath, "%s/objects/%s", tigPath,splittedHash[0]);
	log_dbg("Hashed obj folder Path: %s",folderPath);
	mkdir(folderPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	sprintf(filePath, "%s/%s", folderPath, splittedHash[1]);

	log_dbg("Hashed obj file Path: %s",filePath);

	FILE* fptr = fopen(filePath, "w");
	if(fptr == NULL){
		log_err("Could not create file at %s", filePath);
		exit(EXIT_FAILURE);
	}
	//-------> This is the problem
	log_dbg("header len: %d", strlen(content));
	log_dbg("content len: %d",strlen(content+strlen(content)+1));
	const size_t headerLen = strlen(content);
	const size_t contentLen = strlen(content + headerLen + 1);
	fwrite(content, 1, (headerLen + contentLen), fptr);
	fclose(fptr);

	free(splittedHash);
}	

