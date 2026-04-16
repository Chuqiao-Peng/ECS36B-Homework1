#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_copy = copy_array(arr, 4);
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(arr[i], arr_copy[i]);
    }
    delete[] arr_copy;
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_copy = copy_array(arr, 4);
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(arr[i], i + 1); // in this specific case, arr[i] = i + 1, starting from 0.
    }
    delete[] arr_copy;
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_copy = copy_array(arr, 4);
    for(int i = 0; i < 3; i++) {
        EXPECT_NE(&(arr[i]), &(arr_copy[i]));
    }
    delete[] arr_copy;
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values[i]; // can also use copy(values.begin(), values.end(), arr), and eliminate the for-loop use
    }
    int* arr_copy = copy_array(arr, len);
    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr_copy[i] == values[i]);
    }

    delete[] arr;
    delete[] arr_copy;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values[i]; // can also use copy(values.begin(), values.end(), arr), and eliminate the for-loop use
    }
    int* arr_copy = copy_array(arr, len);
    int rand_index_at_arr_copy = *rc::gen::inRange<int>(0, len);
    int rand_val_changed_at_rand_index = *rc::gen::inRange<int>(0, 1000);
    arr_copy[rand_index_at_arr_copy] = rand_val_changed_at_rand_index; // changed val at arr_copy does not affect original
    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr[i] == values[i]);
    }

    delete[] arr;
    delete[] arr_copy;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values[i]; // can also use copy(values.begin(), values.end(), arr), and eliminate the for-loop use
    }
    int* arr_copy = copy_array(arr, len);
    for(int i = 0; i < len; i++) {
        RC_ASSERT(&(arr_copy[i]) != &(arr[i]));
    }

    delete[] arr;
    delete[] arr_copy;
}



