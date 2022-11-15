template<class T>
T full_euclid(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto g = full_euclid(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

// Works for positive a and b only
template<class T>
T full_euclid_small_x(T a, T b, T &x, T &y) {
    auto g = full_euclid(a, b, x, y);
    auto stepx = b / g;
    auto stepy = a / g;
    auto d = x > 0 ? -x / stepx : (-x + stepx - 1) / stepx;
    x += stepx * d;
    y -= stepy * d;
    return g;
}
