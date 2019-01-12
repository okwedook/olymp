#pragma GCC optimize("O3", "unroll-loops")

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <tuple>
#include <random>
#include <bitset>
#include <queue>

using namespace std;

#define FIXED cout << fixed << setprecision(15)
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define RANDOM srand(85453532)
#define ll long long
#define ld double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define graph vector<vector<int>>
#define pb push_back
#define popb pop_back
#define pf push_front
#define popf pop_front
#define lowb lower_bound
#define upb upper_bound
#define hashmap unordered_map
#define hashset unordered_set
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define eps 1e-9
#define mod 1000000007
#define inf 4000000000000000007ll
#define f first
#define s second
#define shuffle(a) \
    for (int i = 0; i < sz(a); ++i) \
        swap(a[i], a[rand() % sz(a)])

template<class T, class U> inline void checkmin(T &x, U y) { if (y < x) x = y; }
template<class T, class U> inline void checkmax(T &x, U y) { if (y > x) x = y; }
template<class T, class U> inline bool ifmin(T &x, U y) { 
    if (y < x) return x = y, true;
    return false; 
}
template<class T, class U> inline bool ifmax(T &x, U y) { 
    if (y > x) return x = y, true;
    return false; 
}
template<class T> inline void sort(T &a) { sort(all(a)); }
template<class T> inline void rsort(T &a) { sort(rall(a)); }
template<class T> inline void reverse(T &a) { reverse(all(a)); }
template<class T> inline istream& operator>>(istream &stream, vector<T> &a) { 
    for (auto &i : a) stream >> i;
    return stream;
}

struct zet {
    int val;
    zet(ll x = 0) { val = x % mod; if (val < 0) val += mod; }
    zet(ll a, ll b) { *this += a; *this /= b; }

    zet& operator+=(zet const &b) { val += b.val; if (val >= mod) val -= mod; return *this; }
    zet& operator-=(zet const &b) { val -= b.val; if (val < 0) val += mod; return *this; }
    zet& operator*=(zet const &b) { val = (val * (ll)b.val) % mod; return *this; }

    friend zet mypow(zet a, ll n) {
        zet res = 1;
        while (n) { if (n & 1) res *= a; a *= a; n >>= 1; }
        return res;
    }
    friend zet inv(zet a) { return mypow(a, mod - 2); }
    zet& operator/=(zet const& b) { return *this *= inv(b); }
    friend zet operator+(zet a, const zet &b) { return a += b; }
    friend zet operator-(zet a, const zet &b) { return a -= b; }
    friend zet operator-(zet a) { return 0 - a; }
    friend zet operator*(zet a, const zet &b) { return a *= b; }
    friend zet operator/(zet a, const zet &b) { return a /= b; }
    friend ostream& operator<<(ostream& stream, const zet &a) { return stream << a.val; }
    friend bool operator==(zet const &a, zet const &b) { return a.val == b.val; }
    friend bool operator!=(zet const &a, zet const &b) { return a.val == b.val; }
};

const int p = 37;

struct strhash {
    vector<zet> h, pp;
    strhash() {}
    strhash(string s) {
        int n = sz(s);
        h = pp = vector<zet>(n + 2);
        zet curr = 0;
        for (int i = 0; i < n; ++i) { 
            curr = curr * p + s[i];
            h[i] = curr;
        }
        pp[0] = 1;
        for (int i = 1; i < sz(pp); ++i)
            pp[i] = pp[i - 1] * p; 
    }
    inline zet get(int r) {
        if (r < 0) return 0;
        return h[r];
    } 
    inline zet get(int l, int r) {
        return get(r) - get(l - 1) * pp[r - l + 1];
    }
} th;

inline char at(string &s, int ind) {
    if (ind >= sz(s)) return '#';
    return s[ind];
}

signed main() {
    FAST; FIXED; RANDOM;
    string t;
    cin >> t;
    th = strhash(t);
    int n = sz(t);
    vector<int> ta(n);
    for (int i = 0; i < n; ++i) 
        ta[i] = i;
    stable_sort(all(ta), [&] (const int &a, const int &b) {
        int l = -1, r = sz(t) - max(a, b);
        while (r - l > 1) {
            int m = r + l >> 1;
            if (th.get(a, a + m) != th.get(b, b + m)) l = m;
            else r = m;
        }   
        return at(t, a + r) < at(t, b + r);
    });
    for (auto i : ta) cout << i << ' ';
    return 0;
}
