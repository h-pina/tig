#pragma once
#include <openssl/sha.h>

char* sf_addHeaderToContent(char* content, const char* type);
char* sf_hashObject(const char* content);
void saveToObjDb(char* hash, const char* content);
