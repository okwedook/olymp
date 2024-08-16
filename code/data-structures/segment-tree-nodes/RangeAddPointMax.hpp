#include "IndexNode.hpp"

template<class T, bool SupportIndex = true>
struct RangeAddPointMax : conditional_t<SupportIndex, IndexNode, EmptyIndex> {
    T mx = 0;
    T lazy_add = 0;
    RangeAddPointMax() {}
    void upd(T x) {
        mx += x;
        lazy_add += x;
    }
    void upd(const RangeAddPointMax &t) {
        upd(t.lazy_add);
    }
    bool updated() const {
        return lazy_add != 0;
    }
    void unupdate() {
        lazy_add = 0;
    }
    static RangeAddPointMax merge(const RangeAddPointMax &a, const RangeAddPointMax &b) {
        RangeAddPointMax ans;
        if (a.mx >= b.mx) ans.mx = a.mx, ans.copyIndex(a);
        else ans.mx = b.mx, ans.copyIndex(b);
        return ans;
    }
};
