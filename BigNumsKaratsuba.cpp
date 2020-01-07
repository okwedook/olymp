struct num : vector<int> {
    static const int base = 1e9;
    static const int dig = 9;
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
    num multiply(num a, num b) {
        if (sz(a) == 0) return 0;
        while (sz(a) < sz(b)) a.pb(0);
        while (sz(b) < sz(a)) b.pb(0);
        if (sz(a) == 1) return a[0] * (ll)b[0];
        int m = sz(a) / 2;
        num a1 = a.cut(0, m), a2 = a.cut(m, sz(a)),
            b1 = b.cut(0, m), b2 = b.cut(m, sz(b));
        num x1 = multiply(a1, b1), x2 = multiply(a2, b2);
        num x3 = multiply(a1 + a2, b1 + b2);
        x1.clr();
        x2.clr();
        x3 -= x1;
        x3 -= x2;
        return x2.powbase(m << 1) + x3.powbase(m) + x1;
    }
    num& operator*=(const num &x) {
        bool flag = minus ^ x.minus;
        *this = multiply(*this, x);
        minus = flag;
        clr();
        return *this;
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
