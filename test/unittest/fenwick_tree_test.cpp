#include <code/general/base_template.hpp>
#include <code/data-structures/FenwickTree.hpp>

#include <gtest/gtest.h>

TEST(FenwickTreeTest, FunctionalityTest) {
    Fenwick<int> fenw(10);
    fenw.add(3, 5);
    fenw.add(5, 7);
    ASSERT_EQ(fenw.get(3, 5), 12);
    ASSERT_EQ(fenw.get(1, 4), 5);
    ASSERT_EQ(fenw.get(5, 9), 7);
    ASSERT_EQ(fenw.get(0, 0), 0);
}
