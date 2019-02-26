struct vec {
    ll x, y;
    vec() {}
    vec(ll x, ll y) { this->x = x; this->y = y; }
    vec operator+=(const vec &v) { x += v.x; y += v.y; return *this; }
    vec operator-=(const vec &v) { x -= v.x; y -= v.y; return *this; }
    vec operator*=(const ll &k) { x *= k; y *= k; return *this; }
    vec operator-() const { return vec(-x, -y); }
    vec orth() const { return vec(-y, x); }
    ll len2() const { return x * x + y * y; }
    ld len() const { return sqrt(len2()); }
    friend vec operator+(vec a, const vec &b) { return a += b; }
    friend vec operator-(vec a, const vec &b) { return a -= b; }
    friend vec operator*(vec a, const ll &k) { return a *= k; }
    friend ll operator*(const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    friend ll operator/(const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    friend istream& operator>>(istream& str, vec &v) { return str >> v.x >> v.y; }
    friend ostream& operator<<(ostream& str, const vec &v) { return str << v.x << ' ' << v.y; }
    friend bool operator<(const vec &a, const vec &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
};
