#include "tree.h"
#include "object.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createTreeObj(struct TreeObjEntry entries[], uint32_t numEntries){
	char* content = malloc(sizeof(struct TreeObjEntry) * numEntries);
	for(int i = 0; i<numEntries;i++){
		struct TreeObjEntry* currEntry = &entries[i];
		char line[4096] = { 0 };
		sprintf(line, "%d %s %s %s\n", currEntry->mode,  //TODO:Add paddings
						currEntry->type, currEntry->hash, currEntry->path);
		strcat(content, line);
	}
	log_dbg("content before header:\n%s", content);
	char* contentWHeader = sf_addHeaderToContent(content,"tree");
	char* hash = sf_hashObject(contentWHeader);
	printf("%s\n", hash);
	saveToObjDb(hash, contentWHeader);
	free(content);
}





