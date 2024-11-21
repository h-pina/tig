#pragma once
#include <stdint.h>

//#define INDEX_DEFAULT_PATH 

#include <linux/limits.h>
typedef struct{
	int add;
} UpdateIndexArgs;

//This is a simplified version of:
//https://git-scm.com/docs/index-format
typedef struct{
	char ctime[4];
	char mtime[4];
	uint32_t filesize;
	char blobHash[20];
	char path[PATH_MAX]; //maybe this could be less
} IndexEntry;


typedef struct{ } CacheTree;

typedef struct{
	int numEntries;
	IndexEntry* entries;
	//CacheTree??
} Index;


//void createIndex() ????
void updateIndexCmd(UpdateIndexArgs ui);
void addNewEntry();
void updateEntry();


