#include "Math.hpp"

// Counts the primes in O(n^(3/4)) for n and
// every number floor(n / k), where k is an int
ll count_primes(ll n) {
    ll x = 1;
    vector<ll> val;
    while (x * x <= n) {
        val.pb(x);
        ++x;
    }
    auto primes = math::genprimes(x - 1);
    while (x > 0 && n / x <= val.back()) --x;
    while (x > 0) {
        val.pb(n / x);
        --x;
    }
    vector<ll> dp = val;
    for (int a = 1; a <= sz(primes); ++a) {
        int p = primes[a - 1];
        for (int i = sz(dp) - 1, ptr = sz(dp) - 1; val[i] >= p * ll(p); --i) {
            ll need = val[i] / p;
            while (val[ptr] > need) {
                --ptr;
            }
            dp[i] -= max(0ll, dp[ptr] - a);
        }
    }
    return dp.back() - 1;
}