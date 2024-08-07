#include "Kd_Tree.h"

Kd_Tree::Kd_Tree() {
    Kd_Tree(1);
}

Kd_Tree::Node::Node(const int point[]) {
    const size_t sizeArray = sizeof(*point) / sizeof(point[0]);
    this->point = new int[sizeArray];
    for(size_t i = 0; i < sizeArray; i++)
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
    size_t pointSize = sizeof(*point) / sizeof(point[0]);
    if (pointSize != k_dimension)
        return;

    if(!root)
        root = new Node{point};
    else{
        Node * curr = root;

        for(size_t i = 0; i < k_dimension; i++)
            if(point[i % k_dimension] < curr->point[i % k_dimension]){
                if (curr->left)
                    curr = curr->left;
                else{
                    curr->left = new Node{point};
                    break;
                }
            } else {
                int currPoint = curr->point[i % k_dimension];
                int pParameter = point[i % k_dimension];

                if(i == k_dimension - 1 && currPoint == pParameter)
                    return;
                else if(curr->right)
                    curr = curr->right;
                else{
                    curr->right = new Node{point};
                    break;
                }
            }
    }

    size++;
}

void Kd_Tree::insertKey(const std::vector<int> & point) {
    size_t pointSize = point.size();
    if (pointSize != k_dimension)
        return;

    if(!root)
        root = new Node{point};
    else{
        Node * curr = root;

        for(size_t i = 0; i < k_dimension; i++)
            if(point[i % k_dimension] < curr->point[i % k_dimension]){
                if (curr->left)
                    curr = curr->left;
                else{
                    curr->left = new Node{point};
                    break;
                }
            } else {
                int currPoint = curr->point[i % k_dimension];
                int pParameter = point[i % k_dimension];

                if(i == k_dimension - 1 && currPoint == pParameter)
                    return;
                else if(curr->right)
                    curr = curr->right;
                else{
                    curr->right = new Node{point};
                    break;
                }
            }
    }

    size++;
}



#include "deque"

void Kd_Tree::print(std::ostream &ostream) const {
    if(root){
        std::deque<std::pair<int, Node*>> queue;
        queue.push_front({1, root});
        int depth = 0;
        while(!queue.empty()) {
            std::pair<int, Node*> curr = queue.front();
            if(curr.first != depth)
                ostream << "\nDepth " << ++depth << ": ";

            Node* node = curr.second;

            if(node->left)
                queue.push_back({depth, node->left});
            if(node->right)
                queue.push_back({depth, node->right});

            queue.pop_front();
        }
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