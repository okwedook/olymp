struct vec {
	ld x, y;
	vec() { x = y = 0; }
	vec(ld x, ld y) {
		this->x = x;
		this->y = y;
	}
	bool eq(ld a, ld b) {
		return fabs(a - b) < eps;
	}
	ld len2() {
		return x * x + y * y;
	}
	ld len() {
		return sqrt(len2());
	}
	vec orth() {
		return vec(-y, x);
	}
	vec operator+(const vec &a) const {
		return vec(x + a.x, y + a.y);
	}
	vec operator-(const vec &a) const {
		return vec(x - a.x, y - a.y);
	}
	vec operator-() {
		return vec(-x, -y);
	}
	vec operator*(ld k) {
		return vec(x * k, y * k);
	}
	vec operator/(ld k) {
		return vec(x / k, y / k);
	}
	vec norm() {
		ld l = len();
		if (eq(l, 0)) return vec(1, 0);
		return *this / l;
	}
	vec rot(ld sina, ld cosa) {
		return orth() * sina + *this * cosa;
	}
	vec rot(ld alpha) {
		return rot(sin(alpha), cos(alpha));
	}
	bool operator==(const vec &a) const {
		return eq(x, a.x) && eq(y, a.y);
	}
	bool operator<(const vec &a) const {
		if (eq(x, a.x)) return y < a.y;
		return x < a.x;
	}
	ld operator*(const vec &a) const {
		return x * a.x + y * a.y;
	}
	ld operator/(const vec &a) const {
		return x * a.y - y * a.x;
	}
	friend istream& operator>>(istream& stream, vec &a) {
		stream >> a.x >> a.y;
		return stream;
	}
	friend ostream& operator<<(ostream& stream, vec a) {
		stream << a.x << ' ' << a.y;
		return stream;
	}
};
