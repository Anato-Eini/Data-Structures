#include "Kd_Tree.h"

Kd_Tree::Kd_Tree() {
    Kd_Tree(1);
}

Kd_Tree::Kd_Tree(const int k_dimension) : root{nullptr}, size{0}, k_dimension{k_dimension} {}

void Kd_Tree::insertKey(int *point) {

}