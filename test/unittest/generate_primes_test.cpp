#include <code/general/base_template.hpp>
#include <code/math/number-theory/Math.hpp>

#include <gtest/gtest.h>

TEST(GeneratePrimes, BasicTest) {
    for (int N = 1; N <= 100; ++N) {
        vector<bool> is_prime(N + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int d = 2; d * d <= N; ++d) {
            if (is_prime[d]) {
                for (int i = d * d; i <= N; i += d) {
                    is_prime[i] = false;
                }
            }
        }
        vector<int> explicit_check, euratosphene;
        for (int i = 0; i <= N; ++i) {
            if (is_prime[i]) {
                euratosphene.push_back(i);
            }
            if (math::isprime(i)) {
                explicit_check.push_back(i);
            }
        }
        auto linear_primes = math::genprimes(N);
        ASSERT_EQ(explicit_check, euratosphene);
        ASSERT_EQ(explicit_check, linear_primes);
    }
}
