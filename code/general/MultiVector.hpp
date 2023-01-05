template<int Dim, class T>
struct MultiVector : public vector<MultiVector<Dim - 1, T>> {
    static_assert(Dim >= 1, "Vector dimension has to be positive");
    template<typename... Args>
    MultiVector(size_t n = 0, Args... args) : vector<MultiVector<Dim - 1, T>>(n, MultiVector<Dim - 1, T>(args...)) {}
};

template<class T>
struct MultiVector<1, T> : public vector<T> {
    MultiVector(size_t n = 0, const T& val = T()) : vector<T>(n, val) {}
};
