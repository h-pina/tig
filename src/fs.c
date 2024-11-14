#include "fs.h"
#include <linux/limits.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

//TODO: make this more robust
void get_tig_path(char* tigDir){
	//navigate up from current path until .tig folder is found 
	do{
		char cwd[PATH_MAX];
		getcwd(cwd, PATH_MAX);
		if(strlen(cwd) == 1 && cwd[0] == '/') break;
		if( strlen(cwd) < PATH_MAX-4){
			DIR* dir = opendir(".tig");
			if (dir) {
				closedir(dir);
				strcat(cwd, "/.tig");
				strcpy(tigDir, cwd);
				break;
			}
		}
	}while(chdir("..") != -1);
}

