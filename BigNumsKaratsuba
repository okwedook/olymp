const int base = 1000000000;
const int digits = 9;

struct num {
    vector<int> a;
    bool minus = false;
    num() {}
    num(int x) {
        if (x < 0) x = -x, minus = true;
        while (x > 0) a.pb(x % base), x /= base;
    }
    num(ll x) {
        if (x < 0) x = -x, minus = true;
        while (x > 0) a.pb(x % base), x /= base;
    }
    num(string s) {
        if (s[0] == '-') {
            minus = true;
            s = s.substr(1, sz(s) - 1);
        }
        for (int i = sz(s) - digits; i > 0; i -= digits)
            pb(stoi(s.substr(i, digits)));
        pb(stoi(s.substr(0, (sz(s) - 1) % digits + 1)));
        clear();
    }
    template<class T> inline int& operator[](T ind) { return a[ind]; }
    template<class T> inline int operator[](T ind) const { return a[ind]; }
    inline size_t size() const { return a.size(); }
    inline int back() const { return a.back(); }
    template<class T> inline void pb(T x) { a.pb(x); }
    inline num operator-() const {
        num ans = *this;
        ans.minus ^= true;
        return ans;
    }
    inline num abs() const {
        num ans = *this;
        ans.minus = false;
        return ans;
    }
    inline void clear() {
        while (sz(a) && a.back() == 0) a.popb();
        if (sz(a) == 0) minus = false;
    }
    inline bool cmpabs(const num &v) const {
        if (sz(a) != sz(v)) return sz(a) < sz(v);
        for (int i = sz(a) - 1; i >= 0; --i)
            if (a[i] != v[i]) return a[i] < v[i];
        return false;
    }
    inline bool operator==(const num &v) const {
        return minus == v.minus && a == v.a;
    }
    inline bool operator<(const num &v) const {
        if (minus != v.minus) return minus;
        return cmpabs(v);
    }
    inline bool operator<=(const num &v) const { return !(v < *this); }
    inline bool operator>(const num &v) const { return v < *this; }
    inline bool operator>=(const num &v) const { return !(v > *this); }

    inline num operator+(const num& v) const {
        if (minus != v.minus) return *this - v;
        num ans = *this;
        for (int i = 0, cur = 0; i < sz(v) || cur; ++i) {
            if (i == sz(ans)) ans.pb(0);
            ans[i] += (i < sz(v) ? v[i] : 0) + cur;
            cur = ans[i] >= base;
            if (cur) ans[i] -= base;
        }
        ans.clear();
        return ans;
    }
    inline num operator-(const num &v) const {
        if (minus != v.minus) return *this + (-v);
        if (cmpabs(v)) return -(v - *this);
        num ans = *this;
        for (int i = 0, cur = 0; i < sz(v) || cur; ++i) {
            if (i == sz(ans)) ans.pb(0);
            ans[i] -= (i < sz(v) ? v[i] : 0) + cur;
            cur = ans[i] < 0;
            if (cur) ans[i] += base;
        }
        ans.clear();
        return ans;
    }


    inline num cut(int l, int r) const {
        num ans;
        for (int i = l; i < r; ++i)
            ans.pb(a[i]);
        return ans;
    }

    inline num powbase(int x) const {
        num ans;
        for (int i = 0; i < x; ++i) ans.pb(0);
        for (auto i : a) ans.pb(i);
        return ans;
    }

    inline num operator*(const num &v) const {
        num a = *this, b = v;
        while (sz(a) < sz(b)) a.pb(0);
        while (sz(a) > sz(b)) b.pb(0);
        while (__builtin_popcount(sz(a)) != 1) a.pb(0), b.pb(0);
        if (sz(a) == 1) return a[0] * (ll)b[0];
        int n = sz(a);
        int k = n >> 1;
        num a1 = a.cut(0, k), a2 = a.cut(k, n);
        num b1 = b.cut(0, k), b2 = b.cut(k, n);
        num z0 = a1 * b1, z1 = a2 * b2, z2 = (a1 + a2) * (b1 + b2);
        num ans = z0 + (z2 - z0 - z1).powbase(n - k) + z1.powbase(n);
        ans.minus = a.minus ^ b.minus;
        ans.clear();
        return ans;
    }

    inline num div2() const {
        num ans = *this;
        for (int i = sz(ans) - 1, cur = 0; i >= 0; --i) {
            ans[i] += cur;
            cur = ans[i] & 1;
            ans[i] /= 2;
            if (cur) cur = base;
        }
        return ans;
    }

    inline num operator/(const num &v) const {
        num l = 0, r = abs() + 1;
        while (r - l > 1) {
            num m = (r + l).div2();
            if (*this >= v * m) l = m;
            else r = m;
        }
        l.minus = minus;
        l.clear();
        return l;
    }

    inline void operator+=(const num &v) {
        *this = *this + v;
    }

    inline void operator-=(const num &v) {
        *this = *this - v;
    }

    inline void operator*=(const num &v) {
        *this = *this * v;
    }

    inline void operator/=(const num &v) {
        *this = *this / v;
    }

    inline string strval() const {
        string s = "";
        if (minus) s.pb('-');
        if (sz(a)) s += to_string(back());
        else s.pb('0');
        for (int i = sz(a) - 2; i >= 0; --i) {
            string news = to_string(a[i]);
            for (int j = sz(news); j < digits; ++j)
                s.pb('0');
            s += news;
        } 
        return s;
    }
    friend istream& operator>>(istream& stream, num &v) {
        string s;
        stream >> s;
        v = num(s);
        return stream;
    }
    friend ostream& operator<<(ostream& stream, const num &v) {
        if (v.minus) stream << '-';
        if (sz(v) == 0) stream << '0';
        else stream << v.back();
        for (int i = sz(v) - 2; i >= 0; --i) 
            stream << setw(digits) << setfill('0') << v[i];
        return stream;
    }
    friend num sqrt(const num &v) {
        num l = 0, r = v;
        while (r - l > 1) {
            num m = (r + l).div2();
            if (m * m > v) r = m;
            else l = m;
        }
        return l;
    }
    friend string to_string(const num &v) {
        return v.strval();
    }
};
