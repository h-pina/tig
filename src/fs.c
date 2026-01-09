#include "fs.h"
#include "logger.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void getTigPath(char* tigDir){
	log_err("%s folder not found", tigFolderName);
	exit(EXIT_FAILURE);
}

