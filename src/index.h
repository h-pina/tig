#include <limits.h>
#include <stdint.h>

//Check the index-format documentation for the headers info 

struct CacheTree {
	int node;
};

struct IndexEntry{
	char hash[41]; //should this 41 be a constant somewhere??
	char path[PATH_MAX];
	uint32_t mtime_sec;
	uint32_t mtime_nanosec;
};


struct Index{
	//headers --> Should HEaders be here? I dont think so
	int numEntries;
	struct IndexEntry* entries;
	//struct CacheTree ct; --> Should this be inside this struct??
};

//Since the index is a complex structure by itself, I`ll write everything here first, and later I`ll move the specific operations to other files (like fs and object)


//FS
void writeToIndexFile(struct Index* index);
void readFromIndexFile(struct Index* index);

//Index manipulation
void addFileToIndex(struct Index* index,
											char* hash,
											char* path,
											uint32_t mtime_sec,
											uint32_t mtime_nanosec
										);


void updateIndex(struct Index* index);
void printIndexEntries(struct Index* index);

//cache tree
void updateCacheTreeFromIndex();
void writeTreeObjsFromCacheTree(); //git write-tree
void restoreIndex(); //git restore --staged (This relies on the cache tree being done)


