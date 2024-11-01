#include <openssl/sha.h>

#define RESULT_BUFFER_LENGTH 2*SHA_DIGEST_LENGTH

typedef struct{
	int write;
	int useStdin;
} HashObjOpts;

void hashObject(const char* content, HashObjOpts opts, char* result);
void hashObjCmd(HashObjOpts ho);
