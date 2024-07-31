#ifndef DATA_STRUCTURES_SKIPLIST_H
#define DATA_STRUCTURES_SKIPLIST_H

#include "cstring"
#include "random"
#include "ostream"

class SkipList final {

    struct SkipList_Node
    {
        int value;
        SkipList_Node ** next;
    };

public:

    SkipList(const int & rLimit, const int & maxLevel);

    [[nodiscard]] bool keyExist(const int & key);

    SkipList & insertKey(const int & key);

    SkipList & deleteKey(const int & key);

private:

    [[nodiscard]] int get_rNumber() const ;

    int rLimit;

    int maxLevel;

    int level;

    int size;

    SkipList_Node * head;

    friend std::ostream & operator<< (std::ostream & ostream, const SkipList* skip_list);
};

std::ostream & operator<< (std::ostream & ostream, const SkipList* skip_list);

#endif //DATA_STRUCTURES_SKIPLIST_H
