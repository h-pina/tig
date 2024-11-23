#include <limits.h>
#include <inttypes.h>

struct TreeObjEntry{ 
	uint32_t mode;
	char type[10];
	char hash[40];
	char path[PATH_MAX];
};

void createTreeObj(struct TreeObjEntry entries[], uint32_t numEntries);




