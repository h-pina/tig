#include "index.h"
#include "fs.h"
#include "logger.h"
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void getIndexPath(char* indexDir){
	get_tig_path(indexDir);
	strcat(indexDir,"/index");
	log_dbg("index path used: %s", indexDir);
}


void writeToIndexFile(struct Index* index){
	//TODO: read cache tree after finished
	char indexPath[PATH_MAX];
	getIndexPath(indexPath);

	FILE* indexPtr = fopen(indexPath, "wb");
	const char headerSig[] = {'D','I','R','C'};
	fwrite(headerSig, sizeof(char), 4, indexPtr);

	const int headerValues[] = {1, index->numEntries};
	fwrite(headerValues, sizeof(int),2, indexPtr);
	
	for(int i = 0;i<index->numEntries;i++){
		fwrite(&(index->entries[i]), sizeof(struct IndexEntry),1, indexPtr);
	}
}

void readFromIndexFile(struct Index* index){
	//TODO: read cache tree after finished
	char indexPath[PATH_MAX];
	getIndexPath(indexPath);

	FILE* indexPtr = fopen(indexPath, "rb");
	char headerSig[4];
	fread(headerSig, sizeof(char),4,indexPtr);
	log_info("TODO: Implement the Signature checking");

	int headerValues[2];
	fread(headerValues, sizeof(int),2, indexPtr);
	
	log_war("The memory allocation for storing the index entries is never freed, be careful!");
	struct IndexEntry* entries = (struct IndexEntry*)malloc(headerValues[1]*sizeof(struct IndexEntry));
	if(entries == NULL){
		log_err(
			"Out of memory. Malloc could not allocate bytes for storing index entries on memory"
		);
		exit(EXIT_FAILURE);
	}
	for(int i = 0;i<headerValues[1];i++){
		fread(&(entries[i]),sizeof(struct IndexEntry), 1, indexPtr);
	}
	
	index->numEntries = headerValues[1];
	index->entries = entries;
}


void addFileToIndex(struct Index *index, char* hash, char* path, uint32_t mtime_sec, uint32_t mtime_nanosec){
	//fill indexEntry obj
	struct IndexEntry ie;
	
	strcpy(ie.path, path);
	strcpy(ie.hash, hash);

	struct stat ie_stat; 
	lstat(path, &ie_stat);
	ie.mtime_sec = ie_stat.st_mtim.tv_sec;
	ie.mtime_nanosec = ie_stat.st_mtim.tv_nsec;

	//realloc to fit the new index entry
	if( realloc(index->entries, sizeof(struct IndexEntry)) == NULL){
		log_err("Could not expand memory from index to add new index entry");
		exit(EXIT_FAILURE);
	}

	index->entries[index->numEntries] = ie; 
	index->numEntries++;
}


void updateIndexEntry(struct Index* index, struct IndexEntry ie){
	for(int i = 0; i<index->numEntries;i++){
		if(strcmp(index->entries[i].path, ie.path) == 0){
			index->entries[i] = ie;
			return;
		}
	}
}
