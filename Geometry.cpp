struct vec {
    ll x, y;
    vec() {}
    vec(ll x, ll y) {
        this->x = x;
        this->y = y;
    }
    vec operator+(vec a) {
        return vec(x + a.x, y + a.y);
    }
    vec operator-(vec a) {
        return vec(x - a.x, y - a.y);
    }
    ll operator*(vec a) {
        return x * a.x + y * a.y;
    }
    ll operator/(vec a) {
        return x * a.y - y * a.x;
    }
    ll len2() {
        return x * x + y * y;
    }
    ld len() {
        return sqrt(len2());
    }
    friend istream& operator>>(istream& stream, vec &v) {
        cin >> v.x >> v.y;
        return stream;
    }
    friend ostream& operator<<(ostream& stream, vec v) {
        cout << v.x << ' ' << v.y;
        return stream;
    }
};
