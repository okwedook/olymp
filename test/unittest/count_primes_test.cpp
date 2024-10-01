#include <code/general/base_template.hpp>
#include "code/math/number-theory/Math.hpp"
#include "code/math/number-theory/CountPrimes.hpp"

#include <gtest/gtest.h>

TEST(CountPrimes, SmallTest) {
    for (int N = 1; N <= 500; ++N) {
        ASSERT_EQ(math::genprimes(N).size(), count_primes(N));
    }
}

TEST(CountPrimes, BigTest) {
    static const ll thousand = 1000;
    static const ll billion = thousand * thousand * thousand;
    ASSERT_EQ(count_primes(billion + 7), 50847535);
    ASSERT_EQ(count_primes(10 * billion), 455052511);
    ASSERT_EQ(count_primes(100 * billion), 4118054813ll);
    ASSERT_EQ(count_primes(1000 * billion), 37607912018ll);
}
