#ifndef FENWICKTREE_H
#define FENWICKTREE_H
#include <ostream>
#include <vector>

class FenwickTree final {
    int* array;
    int size;

    void buildArray(const int & size);

    void print(std::ostream & ostream) const;

    void update_tree(int index, int && value) const;

public:
    explicit FenwickTree(const int & size);

    FenwickTree();

    FenwickTree & clearArray();

    FenwickTree & buildTree(const int array[], const int & n);

    FenwickTree & buildTree(const std::vector<int> & array);

    /**
     * Must be called whenever there's a change in the original array[i] to update the tree instead of updating the
     * array[i] directly
     * @param array original array
     * @param index index of value to be change
     * @param value new value
     * @return tree itself;
     */
    FenwickTree & updateArray(int array[], const int & index, const int & value);

    /**
     *
     * @param index end index(inclusive)
     * @return get sum from 0 up to end index;
     */
    [[nodiscard]] int getSum(int index) const;

    ~FenwickTree();

    friend std::ostream & operator<<(std::ostream & ostream, const FenwickTree * tree);
};

std::ostream & operator<<(std::ostream & ostream, const FenwickTree * tree);

#endif //FENWICKTREE_H
