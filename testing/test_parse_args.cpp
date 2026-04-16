#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    auto letter_generator = rc::gen::inRange<char>('a', 'z' + 1);
    return rc::gen::container<std::string>(letter_generator);
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> result;
    int len = numbers.size();
    result.resize(len); // resize result vector and initialize space 'len' long with '0's
    for(int i = 0; i < len; i++) {
        result.at(i) = std::to_string(numbers.at(i)); // no need to use pushback, casting
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    char* argv[] = {
        (char*) "Program name",
        (char*) "1",
        (char*) "2",
        (char*) "3"
    };

    int argc = 4;
    int* arr = nullptr;
    int len = 0;
    parse_args(argc, argv, &arr, &len);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that your parse can successfully parse "no" command line arguments.
     */
    char* argv[] = {(char*) "Program name"};
    int argc = 1;
    int* arr = (int*)123;
    int len = 3;

    parse_args(argc, argv, &arr, &len);
    EXPECT_EQ(len, 0);
    EXPECT_EQ(arr, nullptr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    std::string program_name = *word_generator(); // deference to get one word
    std::vector<std::string> args;
    args.push_back(program_name);

    auto numbers = *rc::gen::container<std::vector<int>>(rc::gen::inRange(-1000, 1000)); // rc::gen::arbitrary<std::vector<int>>
    std::vector<std::string> string_vector = vector_of_ints_to_vector_of_strings(numbers);

    for(auto& str : string_vector) {
        args.push_back(str); // store each string into the string vector
    }

    std::vector<char*> argv;
    for(auto& str : args) {
        argv.push_back(str.data()); // store each string into argv as char**
    }
    int argc = argv.size();
    int* arr = nullptr;
    int len = 0;

    parse_args(argc, argv.data(), &arr, &len);
    RC_ASSERT(len == (int)numbers.size());

    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr[i] == (int)numbers.at(i));
    }
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    std::string program_name = *word_generator(); // deference to get one word
    std::vector<std::string> args;
    args.push_back(program_name);

    std::vector<char*> argv;
    for(auto& str : args) {
        argv.push_back(str.data()); // store each string into argv as char**
    }
    int argc = argv.size();
    int* arr = nullptr;
    int len = 3;

    parse_args(argc, argv.data(), &arr, &len);
    RC_ASSERT(len == 0);
    EXPECT_EQ(arr, nullptr);
}
