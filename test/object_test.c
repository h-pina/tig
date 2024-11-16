#include "object.h"
#include "unity.h"
#include "fs.h"
#include "init.h"
#include <openssl/sha.h>
#include <regex.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//TODO: Maybe improve this content lated?
HashObjArgs defaultOpts = {
		.write = 0,
		.useStdin = 0,
		.filename = 0,
};

void setUp(void) {
}

void sha1_must_be_the_same_generated_by_git(){
	const char* content = "Hello World";
	const char* expectedSha1 = "5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689";
  const char* actualSha1 = sf_hashObject(content);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(
		expectedSha1, 
		actualSha1,
		"Generated SHA1 is not compatible with Git "
	);
}


void readContent_must_return_file_contents_correctly(){
	//Arrange
	HashObjArgs opts = {
		.write = 0,
		.useStdin = 0,
		.filename = "test_contents.txt"
	};
	const char* content = "Hello World";
	FILE* fptr  = fopen(opts.filename, "w");
	fputs(content, fptr);
	fclose(fptr);

	//Act
	char contentBuffer[1024];
	readContent(contentBuffer, opts);

	//Assert
	TEST_ASSERT_EQUAL_STRING_MESSAGE(content, contentBuffer, "Content read is different from content inside file");
}

void saveToObjDb_must_create_a_file_in_correct_folder(){
	//Arrange
	setTigFolderName("tig_dbg"); //needed for saveToDb test
	init();

	const char* content = "Hello World";
	char* hash = "5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689";

	//Act
	saveToObjDb(hash, content);

	//Assert
	const char* expectedFilePath = "./tig_dbg/objects/5e/1c309dae7f45e0f39b1bf3ac3cd9db12e7d689";
	char message[1024];

	sprintf(message, "file %s does not exist", expectedFilePath);
	int doesFileExist = access(expectedFilePath, F_OK);
	system("rm -rf ./tig_dbg");
	TEST_ASSERT_EQUAL_INT16_MESSAGE(doesFileExist, 0, message);
}

void tearDown(void) { }

int main(void) {
    UNITY_BEGIN();
		RUN_TEST(sha1_must_be_the_same_generated_by_git);
		RUN_TEST(saveToObjDb_must_create_a_file_in_correct_folder);
		RUN_TEST(readContent_must_return_file_contents_correctly);
    return UNITY_END();
}
