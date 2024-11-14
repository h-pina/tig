#include <string.h>
#include <stdlib.h>
#include "utils.h"
/*
Usage:
Input 
	string: "mystr"
	index: 2

Result
	result[0] = "my/0"
	result[1] = "str/0"
*/

char** sf_splitString(char* string, int index){
	//NOTE: index is a range from 0 to strlen

	char** result = malloc(2*sizeof(char*));

	if(index >= strlen(string)-1){
		result[0] = string;
		result[1] = "";
		return result;
	}

	if(index == 0 ){
		result[0] = "";
		result[1] = string;
		return result;
	}

	result[0] = malloc(index+1*sizeof(char)); 
	strncpy(result[0], string, index+1);
	result[0][index+1] = '\0';

 	int secondStrLen = (strlen(string) - (index + 1));
	char* secondStringStart = string+index+1;
	result[1] = malloc(secondStrLen*sizeof(char)); 
	strcpy(result[1], secondStringStart);

	return result;
}
