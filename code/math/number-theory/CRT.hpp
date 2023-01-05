// Returns -1 if has no solution
ll CRT(ll a1, ll r1, ll a2, ll r2) {
    ll x, y;
    auto g = full_euclid(a1, a2, x, y);
    if ((r2 - r1) % g != 0) {
        return -1;
    }
    ll lcm = a1 / g * a2;
    ll ans = (a1 * x * __int128((r2 - r1) / g) + r1) % lcm;
    ans %= lcm;
    if (ans < 0) {
        ans += lcm;
    }
    return ans;
}
