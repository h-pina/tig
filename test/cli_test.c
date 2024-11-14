#include "cli.h"
#include "object.h"
#include "unity.h"


void setUp(void) { }

void cli_parses_hashObject_cmd_Args(void){
	//Arrange
	char* argv[] = {"hash-object", "-w", "--stdin", "testfile.txt"};
	int argc = 4;

	HashObjArgs expected = {
		.write = 1,
		.useStdin = 1,
		.filename = ""
	};
	
	//Act
	HashObjArgs actual = parseHashObjArgs(argv, argc);

	//Assert
	TEST_ASSERT_EQUAL_INT32_MESSAGE(expected.write, actual.write, "write opt differ");
	TEST_ASSERT_EQUAL_INT32_MESSAGE(expected.useStdin, actual.useStdin, "useStdin opt differ");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected.filename, actual.filename, "filename opt differ");
}

void cli_parses_hashObject_cmd_with_filename(void){
	//Arrange
	char* argv[] = {"hash-object", "-w", "testfile.txt"};
	int argc = 3;

	HashObjArgs expected = {
		.write = 1,
		.useStdin = 0,
		.filename = "testfile.txt"
	};
	
	//Act
	HashObjArgs actual = parseHashObjArgs(argv, argc);

	//Assert
	TEST_ASSERT_EQUAL_INT32_MESSAGE(expected.write, actual.write, "write opt differ");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected.filename, actual.filename, "filename opt differ");
}

void tearDown(void) { }

int main(void) {
    UNITY_BEGIN();
		RUN_TEST(cli_parses_hashObject_cmd_Args);
		RUN_TEST(cli_parses_hashObject_cmd_with_filename);
    return UNITY_END();
}
