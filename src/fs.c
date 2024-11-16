#include "fs.h"
#include "logger.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char* tigFolderName = ".tig";

//TODO: make this more robust
void get_tig_path(char* tigDir){
	//navigate up from current path until .tig folder is found 
	do{
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);
		if(strlen(cwd) == 1 && cwd[0] == '/') break;
		if( strlen(cwd) < PATH_MAX-4){
			DIR* dir = opendir(tigFolderName);
			if (dir) {
				closedir(dir);
				strcat(cwd, "/");
				strcat(cwd, tigFolderName);
				strcpy(tigDir, cwd);
				return;
			}
		}
	}while(chdir("..") != -1);
	
	log_err("%s folder not found", tigFolderName);
	exit(EXIT_FAILURE);
}

//This is currently only used for unit testing
//It is important to remember that since this is a cli
//application, the program is restarted at every cli command
//so the  changes made by this function wont persist to the next
//command
void setTigFolderName(const char* name){
	tigFolderName = strdup(name);
}
const char* getTigFolderName(){
	return tigFolderName;
}
