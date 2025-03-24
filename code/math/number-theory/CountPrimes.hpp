// Counts the primes in O(n^(3/4)) for n and
// every number floor(n / k), where k is an int
struct PrimeCounter {
    PrimeCounter(ll n) : n(n) {
        vector<ll> val;
        val.reserve(2 * sqrt(n) + 2);
        ll x = 1;
        while (x * x <= n) {
            val.pb(x);
            ++x;
        }
        sq = x - 1;
        while (x > 0 && n / x <= val.back()) --x;
        while (x > 0) {
            val.pb(n / x);
            --x;
        }
        dp = val;
        int a = 0;
        for (ll p = 2; p * p <= n; ++p) {
            if (dp[p - 1] == dp[p - 2]) continue;
            ++a;
            for (int i = sz(dp) - 1; val[i] >= p * p; --i) {
                dp[i] -= dp[get_ind(val[i] / p)] - a;
            }
        }
    }
    ll countPrimes() const {
        return dp.back() - 1;
    }
    ll countPrimes(ll x) const {
        return dp[get_ind(x)] - 1;
    }
    int get_ind(ll x) const {
        return x <= sq ? x - 1 : sz(dp) - (n / x);
    }
    ll n, sq;
    vector<ll> dp;
};
