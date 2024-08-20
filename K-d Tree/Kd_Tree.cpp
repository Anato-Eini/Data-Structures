#include "Kd_Tree.h"

Kd_Tree::Kd_Tree() {
    Kd_Tree(1);
}

Kd_Tree::Node::Node(const int point[], int size) {
    this->point = new int[size];
    for(size_t i = 0; i < size; i++)
        this->point[i] = point[i];

    left = right = nullptr;
}

Kd_Tree::Node::Node(const std::vector<int> & point){
    const size_t sizeArray = point.size();
    this->point = new int[sizeArray];
    for(size_t i = 0; i < sizeArray; i++)
        this->point[i] = point[i];

    left = right = nullptr;
}

Kd_Tree::Node::~Node(){
    delete point;
    delete right;
    delete left;
}

Kd_Tree::Kd_Tree(const int k_dimension) : root{nullptr}, size{0}, k_dimension{k_dimension} {}

void Kd_Tree::insertKey(const int point[]) {
    if(!root)
        root = new Node{point, k_dimension};
    else{
        Node * curr = root;

        for(int i = 0; true; i = ++i % k_dimension)
            if(point[i] < curr->point[i]){
                if (curr->left)
                    curr = curr->left;
                else{
                    curr->left = new Node{point, k_dimension};
                    break;
                }
            } else if (curr->right)
                    curr = curr->right;
            else {
                curr->right = new Node{point, k_dimension};
                break;
            }
    }

    size++;
}

void Kd_Tree::insertKey(const std::vector<int> & point) {
    if(!root)
        root = new Node{point};
    else{
        Node * curr = root;

        for(int i = 0; true; i = ++i % k_dimension)
            if(point[i] < curr->point[i]){
                if (curr->left)
                    curr = curr->left;
                else{
                    curr->left = new Node{point};
                    break;
                }
            } else if (curr->right)
                    curr = curr->right;
            else {
                curr->right = new Node{point};
                break;
            }
    }

    size++;
}

void Kd_Tree::deleteKey(const int point[]){

}

bool Kd_Tree::keyExist(const int *point) const {
    if(root){
        Node* curr = root;

        for(int i = 0; true; i = ++i % k_dimension){

        }
    }
    return false;
}

#include "deque"

void Kd_Tree::print(std::ostream &ostream) const {
    ostream << "Size: " << size << '\n';

    if(root){
        std::deque<std::pair<int, Node*>> queue;
        queue.push_front({1, root});
        int depth = 0;

        while(!queue.empty()) {
            std::pair<int, Node*> curr = queue.front();

            if(curr.first != depth)
                ostream << "\nDepth " << (depth = curr.first) << ": ";

            Node* node = curr.second;

            ostream << "| ";
            for (int i = 0; i < k_dimension; i++)
                ostream << node->point[i] << " ";
            ostream << "|";

            if(node->left)
                queue.push_back({depth + 1, node->left});
            if(node->right)
                queue.push_back({depth + 1, node->right});

            queue.pop_front();
        }

        ostream << '\n';
    }
}

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree * tree){
    tree->print(ostream);

    return ostream;
}

std::ostream & operator<<(std::ostream & ostream, const Kd_Tree & tree){
    tree.print(ostream);

    return ostream;
}