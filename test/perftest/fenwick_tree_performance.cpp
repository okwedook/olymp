#include <code/general/base_template.hpp>
#include <code/data-structures/FenwickTree.hpp>

#include <gtest/gtest.h>

TEST(FenwickTreePerformance, BasicPerformanceTest) {
    constexpr int N = 1e6;
    constexpr int Q = 1e8;
    Fenwick<int> tree(N);
    for (int i = 0; i < Q; ++i) {
        // tree.add(gen() % N, gen());
	tree.add(i % N, i);
        // int l = gen() % N, r = gen() % N;
        // if (l > r) swap(l, r);
        // tree.get(l, r);
	tree.get(i % N);
    }
}
