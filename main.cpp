#include <iostream>

#include "vector.h"
#include "particle.h"
#include "nbody.h"

#include <gtest/gtest.h>

TEST(VECTOR, Adding) {
    phys::vector<3, double> a{{0,2,-1}}, b{{1,-2,1}};
    ASSERT_DOUBLE_EQ(1, (a+b)[x]);
    ASSERT_DOUBLE_EQ(0, (a+b)[y]);
    ASSERT_DOUBLE_EQ(0, (a+b)[z]);
}

TEST(VECTOR, multiply) {
    phys::vector<3, double> a{{1,2,3}};
    a *= 3.0;
    ASSERT_DOUBLE_EQ(3, a[x]);
    ASSERT_DOUBLE_EQ(0.5, (a/=6)[x]);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
