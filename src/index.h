#include <cstdint>
#include <limits.h>

//Check the index-format documentation for the headers info 


struct CacheTree {
	int node;
};

struct IndexEntry{
	char hash[41]; //should this 41 be a constant somewhere??
	char path[PATH_MAX];
};


struct Index{
	//headers --> Should HEaders be here? I dont think so
	uint32_t numEntries;
	IndexEntry* entries;
	CacheTree ct;
};

char lastTreeHash[41]; //used when creating commit-tree

//Since the index is a complex structure by itself, I`ll write everything here firs, and later I`ll move the specific operations to other files (like fs and object)

void initIndex(); //git init --> this can maybe call updateCacheEntries 
void updateIndexEntries(); //git update-index
void restoreIndex(); //git restore --staged

//cache tree
void updateCacheTreeFromIndex();
void writeTreeObjsFromCacheTree(); //git write-tree


