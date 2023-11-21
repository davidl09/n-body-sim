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

TEST(VECTOR, compare) {
    phys::vector<3, double> a{{1,2,3}}, b{{0.5, 1, 1.5}};
    ASSERT_TRUE((a/2) == b);
}

int run_tests(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    phys::nbodysim<long double> sim(0, 0.001, 101, 100, 0.01);
    sim.add_particle({100, {{0, 0, 0}}});
    sim.add_particle({100, {1, 0, 0}});
    sim.print();
    sim.run(0.1);
    sim.print();
    return RUN_ALL_TESTS();
}
