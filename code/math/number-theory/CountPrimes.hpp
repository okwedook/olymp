// Counts the primes in O(n^(3/4)) for n and
// every number floor(n / k), where k is an int
ll count_primes(ll n) {
    vector<ll> val;
    val.reserve(2 * sqrt(n) + 2);
    ll x = 1;
    while (x * x <= n) {
        val.pb(x);
        ++x;
    }
    ll sq = x - 1;
    while (x > 0 && n / x <= val.back()) --x;
    while (x > 0) {
        val.pb(n / x);
        --x;
    }
    auto get_ind = [sq, n, &val](ll x) {
        return x <= sq ? x - 1 : sz(val) - (n / x);
    };
    vector<ll> dp = val;
    int a = 0;
    for (ll p = 2; p * p <= n; ++p) {
        if (dp[p - 1] == dp[p - 2]) continue;
        ++a;
        for (int i = sz(dp) - 1; val[i] >= p * p; --i) {
            dp[i] -= dp[get_ind(val[i] / p)] - a;
        }
    }
    return dp.back() - 1;
}
