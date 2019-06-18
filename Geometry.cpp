struct pos {
    ll x, y;
    pos() {}
    pos(ll x, ll y) { this->x = x; this->y = y; }
    pos operator+=(const pos &v) { x += v.x; y += v.y; return *this; }
    pos operator-=(const pos &v) { x -= v.x; y -= v.y; return *this; }
    pos operator*=(const ll &k) { x *= k; y *= k; return *this; }
    pos operator-() const { return pos(-x, -y); }
    pos orth() const { return pos(-y, x); }
    ll len2() const { return x * x + y * y; }
    ld len() const { return sqrt(len2()); }
    friend pos operator+(pos a, const pos &b) { return a += b; }
    friend pos operator-(pos a, const pos &b) { return a -= b; }
    friend pos operator*(pos a, const ll &k) { return a *= k; }
    friend ll operator*(const pos &a, const pos &b) { return a.x * b.x + a.y * b.y; }
    friend ll operator/(const pos &a, const pos &b) { return a.x * b.y - a.y * b.x; }
    friend istream& operator>>(istream& str, pos &v) { return str >> v.x >> v.y; }
    friend ostream& operator<<(ostream& str, const pos &v) { return str << v.x << ' ' << v.y; }
    friend bool operator<(const pos &a, const pos &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
    friend bool operator==(const pos &a, const pos &b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const pos &a, const pos &b) { return a.x != b.x || a.y != b.y; }
};
