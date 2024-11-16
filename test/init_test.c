#include "unity.h"
#include "init.h"
#include "fs.h"
#include <stdio.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <regex.h>
#include <dirent.h>

void setUp(void) {
	setTigFolderName("tig_dbg");
}

void tig_initializes_correct_folder_structure(){
	//Arrange
	char* expectedDirs[] = {
		"./tig_dbg",
		"./tig_dbg/objects"
	};

	//Act
	init();

	//Assert
	for(int i = 0; i<2;i++){
		DIR* dir = opendir(expectedDirs[i]);
		char message[1024];
		sprintf(message, "folder %s does not exist",expectedDirs[i]);
		TEST_ASSERT_NOT_NULL_MESSAGE(dir, message);
		if(dir){ //if passed, close the dir
			closedir(dir);
		}
	}
}

void tearDown(void) { }

int main(void) {
    UNITY_BEGIN();
		RUN_TEST(tig_initializes_correct_folder_structure);
    return UNITY_END();
}
