#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = 1, b = 2;
    swap(&a, &b);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1); // a = 2 and b = 1 after a valid swap
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int arr[4] = {1, 3, 2, 4};
    swap(&(arr[1]), &(arr[2]));
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start, b = b_start;

    swap(&a, &b);

    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    int len = values.size();
    std::vector<int> arr = values;

    // generate 2 indicies of the array
    int i = *rc::gen::inRange<int>(0, len);
    int j = *rc::gen::inRange<int>(0, len);

    int a = arr[i];
    int b = arr[j];

    swap(&a, &b);

    RC_ASSERT(arr[i] == b);
    RC_ASSERT(arr[j] == a);
}
