#pragma once
#include <openssl/sha.h>

#define RESULT_BUFFER_LENGTH 2*SHA_DIGEST_LENGTH

typedef struct{
	int write;
	int useStdin;
	char filename[100];
} HashObjArgs;

void readContent(const char* contentBuffer, int useStdin);
void hashObject(const char* content, HashObjArgs opts, char* result);
void saveToObjDb(const char* hash, const char* content);
void hashObjCmd(HashObjArgs ho);
