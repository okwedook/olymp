#include <gtest/gtest.h>

#include <code/general/base_template.hpp>
#include <code/general/custom_io.hpp>
#include <code/general/debugger.hpp>
#include <code/data-structures/TreapGeneral.hpp>

struct node_min : node<pii> {
    pii mn;
    node_min() {}
    node_min(const Key &k) : node<pii>(k), mn(k) {}   
    static pii getmn(pnode t) {
        return Treap<node_min>::pool[t].mn;
    }
    void upd() {
        mn = key;
        if (l != nullnode) {
            chmin(mn, getmn(l));
        }
        if (r != nullnode) {
            chmin(mn, getmn(r));
        }
    }
};

TEST(GeneralTreapTest, TreapPiiMinTest) {
    using treap = Treap<node_min>;
    pnode tree = treap::new_node(pii{1, 2});
    tree = treap::merge(tree, treap::new_node(pii{3, 4}));
    ASSERT_EQ(treap::to_string(tree), "{1,2} {3,4} ");
    tree = treap::merge(tree, treap::new_node(pii{5, 6}));
    ASSERT_EQ(treap::to_string(tree), "{1,2} {3,4} {5,6} ");
    pnode l, r;
    treap::splitval(tree, {3, 4}, l, r);
    ASSERT_EQ(treap::to_string(l), "{1,2} ");
    ASSERT_EQ(treap::to_string(r), "{3,4} {5,6} ");
    tree = treap::merge(l, r);
    ASSERT_EQ(treap::to_string(tree), "{1,2} {3,4} {5,6} ");
    treap::splitvalup(tree, {3, 4}, l, r);
    ASSERT_EQ(treap::to_string(l), "{1,2} {3,4} ");
    ASSERT_EQ(treap::to_string(r), "{5,6} ");
}
