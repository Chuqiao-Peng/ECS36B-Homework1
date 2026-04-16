#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int arr[4] = {1, 2, 3, 4};
    int min_index = min_index_of_array(arr, 4);
    EXPECT_EQ(min_index, 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int arr[4] = {4, 3, 2, 1};
    int min_index = min_index_of_array(arr, 4);
    EXPECT_EQ(min_index, 3);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int arr[4] = {2, 1, 3, 4};
    int min_index = min_index_of_array(arr, 4);
    EXPECT_EQ(min_index, 1);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int arr[4] = {1, 1, 3, 4};
    int min_index = min_index_of_array(arr, 4);
    EXPECT_EQ(min_index, 0);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int arr[4] = {1, 2, 3, 4};
    int min_index = min_index_of_array(arr, 4);
    EXPECT_EQ(min_index, 0);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              (std::vector<int> values)) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    int len = values.size();
    int* arr = new int[len];

    for(int i = 0; i < len; i++) {
        arr[i] = values.at(i);
    }

    int min_index = min_index_of_array(arr, len);
    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr[min_index] <= arr[i]);
    }

    delete[] arr;
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              (std::vector<int> values)) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int len = values.size();
    int* arr = new int[len];

    for(int i = 0; i < len; i++) {
        arr[i] = values.at(i);
    }

    min_index_of_array(arr, len); // call to min_index(), but no need to create a variable that holds the function's return value
    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr[i] == values.at(i));
    }

    delete[] arr;
}
