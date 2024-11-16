#include <linux/limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include "fs.h"
#include "logger.h"
#include <unistd.h>

void init(){
	char* tigDirTree[] = {
		"%s",
		"%s/objects"
	};
	char tigBasePath[PATH_MAX], dirPath[PATH_MAX]; //change this;

	for(int i = 0; i<2;i++){
		sprintf(dirPath, tigDirTree[i], tigFolderName);
		log_dbg("%s", dirPath);
		mkdir(dirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
}
