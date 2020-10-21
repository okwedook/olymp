bool eq(ld a, ld b) { return abs(a - b) < eps; }

struct vec {
    ld x, y;
    vec() {}
    vec(ld x, ld y) { this->x = x; this->y = y; }
    vec operator+=(const vec &v) { x += v.x; y += v.y; return *this; }
    vec operator-=(const vec &v) { x -= v.x; y -= v.y; return *this; }
    vec operator*=(ld k) { x *= k; y *= k; return *this; }
    vec operator/=(ld k) { x /= k; y /= k; return *this; }
    vec operator-() const { return vec(-x, -y); }
    vec orth() const { return vec(-y, x); }
    ld len2() const { return x * x + y * y; }
    ld len() const { return sqrt(len2()); }
    friend vec operator+(vec a, const vec &b) { return a += b; }
    friend vec operator-(vec a, const vec &b) { return a -= b; }
    friend vec operator*(vec a, const ld &k) { return a *= k; }
    friend vec operator/(vec a, const ld &k) { return a /= k; }
    friend ld operator*(const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    friend ld operator/(const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    vec rot(ld sina, ld cosa) { return orth() * sina + *this * cosa; }
    vec rot(ld alpha) { return rot(sin(alpha), cos(alpha)); }
    friend istream& operator>>(istream& str, vec &v) { return str >> v.x >> v.y; }
    friend ostream& operator<<(ostream& str, const vec &v) { return str << v.x << ' ' << v.y; }
    friend bool operator==(const vec &a, const vec &b) { return eq(a.x, b.x) && eq(a.y, b.y); }
    friend bool operator!=(const vec &a, const vec &b) { return !(a == b); }
    friend bool operator<(const vec &a, const vec &b) { return (eq(a.x, b.x) ? a.y < b.y : a.x < b.x); }
};
