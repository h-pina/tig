#include <string.h>
#include <stdlib.h>
char** sf_splitString(const char* string, int index){
	//create an array to store result 
	size_t strLen = strlen(string);
	char** result = malloc(2*sizeof(char*));

	// folderName  -> 2 chars + \0
	result[0] = malloc(index+1*sizeof(char)); 
	strncpy(result[0], string, index+1);
	result[0][index+1] = '\0';
	result[1] = malloc((strlen(string) - (index + 1))*sizeof(char)); 
	strcpy(result[1], string+index+1);//maybe add a \0
	return result;
}

