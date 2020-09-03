struct num : vector<int> {
    static const int base = 1e3;
    static const int dig = 3;
    bool minus = false;
    num() {}
    num(int x) { if (x < 0) minus = true, x = -x; while (x > 0) pb(x % base), x /= base; }
    num(ll x) { if (x < 0) minus = true, x = -x; while (x > 0) pb(x % base), x /= base; }
    template<class It> num(It begin, It end) { while (begin < end) pb(*begin++); }
    inline int& get(int ind) { return (*this)[ind]; }
    inline int get(int ind) const { return (*this)[ind]; }
    inline void clr() { while (!empty() && back() == 0) popb(); if (empty()) minus = false; }
    friend string to_string(const num &x) {
        string ans;
        if (x.minus) ans += '-';
        ans += (sz(x) == 0 ? "0" : to_string(x.back()));
        for (int i = sz(x) - 2; i >= 0; --i) {
            string add = to_string(x[i]);
            for (int j = sz(add); j < dig; ++j) ans += '0';
            ans += add;
        }
        return ans;
    }
    bool cmpabs(const num &x) const { //abs(this) < abs(x)
        if (size() != sz(x)) return size() < sz(x);
        for (int i = sz(x) - 1; i >= 0; --i)
            if (get(i) != x[i]) return get(i) < x[i];
        return false;
    }
    num operator-() const {
        num ans = *this;
        ans.minus ^= true;
        return ans;
    }
    num& operator+=(const num &x) {
        if (minus != x.minus) return *this -= (-x);
        for (int i = 0, cur = 0; i < sz(x) || cur; ++i) {
            if (i == size()) pb(0);
            if (i < sz(x)) get(i) += x[i];
            get(i) += cur;
            cur = get(i) >= base;
            if (cur) get(i) -= base;
        }
        return *this;
    }
    num& operator-=(const num &x) {
        if (minus != x.minus) return *this += (-x);
        if (cmpabs(x)) return *this = -(x - *this);
        for (int i = 0, cur = 0; i < sz(x) || cur; ++i) {
            if (i == size()) pb(0);
            if (i < sz(x)) get(i) -= x[i];
            get(i) -= cur;
            cur = get(i) < 0;
            if (cur) get(i) += base;
        }
        clr();
        return *this;
    }
    num powbase(int p) const {
        num ans;
        for (int i = 0; i < p; ++i) ans.pb(0);
        for (auto i : *this) ans.pb(i);
        return ans;
    }
    num cut(int l, int r) const {
        return num(begin() + l, begin() + r);
    }
    num& operator/=(const num &x) {
        
    }

    bool operator<(const num &x) const {
        if (minus != x.minus) return minus;
        return cmpabs(x) ^ minus;
    }
    bool operator>(const num &x) const {
        return x < *this;
    }
    bool operator<=(const num &x) const {
        return !(*this > x);
    }
    bool operator>=(const num &x) {
        return x <= *this;
    }
    bool operator!=(const num &x) {
        return !(*this == x);
    }

    friend istream& operator>>(istream& str, num &x) {
        string s;
        str >> s;
        x.minus = false;
        x.clear();
        if (s[0] == '-') x.minus = true, s.erase(s.begin());
        for (int i = sz(s) - dig; i > 0; i -= dig)
            x.pb(stoi(s.substr(i, dig)));
        x.pb(stoi(s.substr(0, (sz(s) - 1) % dig + 1)));
        return str;
    }
    friend ostream& operator<<(ostream& str, const num &x) {
        return str << to_string(x);
    }

    typedef complex<ld> bs;

    void fft(vector<bs> &a, int n) {
        int LOG = log2(n);
        vector<int> ind(n);
        for (int i = 1; i < n; ++i) {
            int last = 31 - __builtin_clz(i);
            ind[i] = ind[i ^ (1 << last)] | (1 << LOG - 1 - last);
        }
        vector<bs> cp(n);
        for (int i = 0; i < n; ++i)
            cp[i] = a[ind[i]];
        std::swap(a, cp);
        for (int len = 2; len <= n; len *= 2) {
            bs w(cos(2 * M_PI / len), sin(2 * M_PI / len));
            int l2 = len >> 1, mask = l2 - 1;
            for (int i = 0; i < n; i += len) {
                bs c(1, 0);
                for (int j = 0; j < len; ++j) {
                    cp[i + j] = a[i + (j & mask)] + a[i + l2 + (j & mask)] * c;
                    c *= w;
                }
            }
            std::swap(cp, a);
        }
    }

    num& operator*=(const num &b) {
        minus ^= b.minus;
        vector<bs> fa(all(*this)), fb(all(b));
        int x = 1;
        while (x < sz(fa)) x *= 2;
        while (x < sz(fb)) x *= 2;
        x *= 2;
        fa.resize(x);
        fb.resize(x);
        fft(fa, x);
        fft(fb, x);
        vector<bs> v(x);
        for (int i = 0; i < x; ++i) v[i] = fa[i] * fb[i];
        fft(v, x);
        reverse(v.begin() + 1, v.end());
        for (auto &i : v) i /= x;
        ll was = 0;
        clear();
        for (auto i : v) {
            was += (ll)(i.real() + 0.5);
            pb(was % base);
            was /= base;
        }
        clr();
        return *this;
    }

    friend num mypow(num a, int n) {
        num ans = 1;
        while (n > 0) {
            if (n & 1) ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }

    friend num operator+(num a, const num &b) { return a += b; }
    friend num operator-(num a, const num &b) { return a -= b; }
    friend num operator*(num a, const num &b) { return a *= b; }
    friend num operator/(num a, const num &b) { return a /= b; }
};
