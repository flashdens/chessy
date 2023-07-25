#include <gtest/gtest.h>

#include "utils.h"
#include "enums.h"

// Test macros.
TEST(utils, FR2SQ) {
    // Test case 1: File 3, Rank 6 (2,5)
    EXPECT_EQ(FR2SQ(FILE_D, RANK_6), 74);

    // Test case 2: File 7, Rank 3 (6,2)
    EXPECT_EQ(FR2SQ(FILE_H, RANK_3), 48);

    // Test case 3: File A, Rank 1 (0, 0)
    EXPECT_EQ(FR2SQ(FILE_A, RANK_1), 21);

    // Test case 4: File H, Rank 8 (8, 8)
    EXPECT_EQ(FR2SQ(FILE_H, RANK_8), 98);
}
