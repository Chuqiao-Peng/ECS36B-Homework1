#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_sorted = get_sorted(arr, 4);
    EXPECT_EQ(arr_sorted[0], 1);
    EXPECT_EQ(arr_sorted[1], 2);
    EXPECT_EQ(arr_sorted[2], 3);
    EXPECT_EQ(arr_sorted[3], 4);
    free(arr_sorted);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {4, 3, 2, 1};
    int* arr_sorted = get_sorted(arr, 4);
    EXPECT_EQ(arr_sorted[0], 1);
    EXPECT_EQ(arr_sorted[1], 2);
    EXPECT_EQ(arr_sorted[2], 3);
    EXPECT_EQ(arr_sorted[3], 4);
    free(arr_sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {4, 2, 3, 1};
    int* arr_sorted = get_sorted(arr, 4);
    EXPECT_EQ(arr_sorted[0], 1);
    EXPECT_EQ(arr_sorted[1], 2);
    EXPECT_EQ(arr_sorted[2], 3);
    EXPECT_EQ(arr_sorted[3], 4);
    free(arr_sorted);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[5] = {1, 4, 2, 3, 2};
    int* arr_sorted = get_sorted(arr, 5);
    EXPECT_EQ(arr_sorted[0], 1);
    EXPECT_EQ(arr_sorted[1], 2);
    EXPECT_EQ(arr_sorted[2], 2);
    EXPECT_EQ(arr_sorted[3], 3);
    EXPECT_EQ(arr_sorted[4], 4);
    free(arr_sorted);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_sorted = get_sorted(arr, 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    free(arr_sorted);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[4] = {1, 2, 3, 4};
    int* arr_sorted = get_sorted(arr, 4);
    EXPECT_NE(&(arr[0]), &(arr_sorted[0]));
    EXPECT_NE(&(arr[1]), &(arr_sorted[1]));
    EXPECT_NE(&(arr[2]), &(arr_sorted[2]));
    EXPECT_NE(&(arr[3]), &(arr_sorted[3]));
    free(arr_sorted);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values.at(i);
    }

    int* arr_sorted = get_sorted(arr, len); // different to make_sorted() as test_sorted() returns an int*
    for(int i = 0; i < len - 1; i++) {
        RC_ASSERT(arr_sorted[i] <= arr_sorted[i + 1]);
    }

    delete[] arr;
    delete[] arr_sorted;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values[i];
    }

    int* sorted_array = get_sorted(arr, len); // call to get_sorted(), but no need to create a variable that holds the function's return value
    for(int i = 0; i < len; i++) {
        RC_ASSERT(arr[i] == values[i]);
    }

    delete[] arr;
    free(sorted_array);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* arr = new int[len];
    for(int i = 0; i < len; i++) {
        arr[i] = values[i];
    }

    int* arr_sorted = get_sorted(arr, len);
    for(int i = 0; i < len; i++) {
        RC_ASSERT(&(arr_sorted[i]) != &(values[i]));
    }

    delete[] arr;
    delete[] arr_sorted;
}











