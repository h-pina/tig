#include "object.h"
#include "unity.h"
#include <openssl/sha.h>
#include <regex.h>

//TODO: Maybe improve this content lated?
HashObjArgs defaultOpts = {
		.write = 0,
		.useStdin = 0,
		.filename = 0,
};
static const char* content = "Hello World";

void setUp(void) { }

void sha1_must_be_the_same_generated_by_git(){
	const char* expectedSha1 = "5e1c309dae7f45e0f39b1bf3ac3cd9db12e7d689";
  const char* actualSha1 = sf_hashObject(content);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(
		expectedSha1, 
		actualSha1,
		"Generated SHA1 is not compatible with Git "
	);
}

void w_cli_option_must_create_a_file_in_correct_folder(){
	TEST_IGNORE_MESSAGE("Test not implemented");
}
void sha1_must_return_error_on_empty_content(){
	TEST_IGNORE_MESSAGE("Test not implemented");
}

void readContent_must_return_error_when_no_reading_sources_are_defined(){
	TEST_IGNORE_MESSAGE("Test not implemented");
}

void tearDown(void) { }

int main(void) {
    UNITY_BEGIN();
		RUN_TEST(w_cli_option_must_create_a_file_in_correct_folder);
		RUN_TEST(sha1_must_be_the_same_generated_by_git);
		RUN_TEST(w_cli_option_must_create_a_file_in_correct_folder);
		RUN_TEST(sha1_must_return_error_on_empty_content);
		RUN_TEST(readContent_must_return_error_when_no_reading_sources_are_defined);
    return UNITY_END();
}
