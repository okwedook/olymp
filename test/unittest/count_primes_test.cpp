#include <code/general/base_template.hpp>
#include "code/math/number-theory/CountPrimes.hpp"

#include <gtest/gtest.h>

TEST(CountPrimes, SmallTest) {
    for (int N = 1; N <= 500; ++N) {
        ASSERT_EQ(math::genprimes(N).size(), count_primes(N));
    }
}

TEST(CountPrimes, BigTest) {
    ASSERT_EQ(count_primes(10 * 1000ll * 1000ll * 1000ll), 455052511);
    ASSERT_EQ(count_primes(1000 * 1000 * 1000 + 7), 50847535);
}
