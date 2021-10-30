// Author: Mikhail Pogodin (okwedook)
//
// Function, which applies gauss elimination with some optimizations
//
// Check tasks: https://judge.yosupo.jp/problem/matrix_det, https://judge.yosupo.jp/problem/sparse_matrix_det

template<class T>
void applyGauss(vector<vector<T>> &v) {
    if (sz(v) == 0) {
        return;
    }
    int n = sz(v), m = sz(v[0]);
    auto apply = [&v, m](int i, int j, T mul) { // v[i] += v[j] * mul
        for (int t = 0; t < m; ++t) {
            v[i][t] += v[j][t] * mul;
        }
    };
    int ptr = 0;
    for (int j = 0; j < m && ptr < n; ++j) {
        if (v[ptr][j] == 0) {
            for (int i = ptr + 1; i < n; ++i) {
                if (v[i][j] != 0) {
                    apply(ptr, i, 1);
                    apply(i, ptr, -1);
                    break;
                }
            }
            if (v[ptr][j] == 0) {
                continue;
            }
        }
        for (int i = ptr + 1; i < n; ++i) {
            if (v[i][j] != 0) {
                apply(i, ptr, -v[i][j] / v[ptr][j]);
            }
        }
        ++ptr;
    }
}

