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
  const char* actualSha1 = sf_hashObject(content, defaultOpts);
	TEST_ASSERT_EQUAL_STRING_MESSAGE(
		expectedSha1, 
		actualSha1,
		"Generated SHA1 is not compatible with Git "
	);
}

void w_cli_option_must_create_a_file_in_correct_folder_(){
	TEST_IGNORE_MESSAGE("This Test Was Ignored On Purpose");
}

void tearDown(void) { }

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
		RUN_TEST(sha1_must_be_the_same_generated_by_git);
		RUN_TEST(w_cli_option_must_create_a_file_in_correct_folder_);
    return UNITY_END();
}
