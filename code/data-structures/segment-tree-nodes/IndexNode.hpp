struct EmptyIndex {
    void copyIndex(EmptyIndex) {}
};

struct IndexNode {
    // The default value is -1 and is user initialized if needed
    int index = -1;
    void copyIndex(const IndexNode& other) {
        index = other.index;
    }
};
