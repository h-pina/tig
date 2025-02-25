#pragma once

typedef struct{
	int write;
	int useStdin;
	char filename[100];
} HashObjArgs;

void readContent(char* contentBuffer, HashObjArgs opts);
void hashObjCmd(HashObjArgs ho, char* hashBuffer);
