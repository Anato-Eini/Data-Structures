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

        ~SkipList_Node();
    };

    [[nodiscard]] int get_rNumber() const ;

    [[nodiscard]] SkipList_Node ** get_update_list_node(const int & key) const;

public:

    SkipList(const float & rLimit, const int & maxLevel);

    [[nodiscard]] bool keyExist(const int & key) const;

    SkipList & insertKey(const int & key);

    SkipList & deleteKey(const int & key);

    ~SkipList();

private:

    float rLimit;

    int maxLevel;

    int level;

    int size;

    SkipList_Node * head;

    friend std::ostream & operator<< (std::ostream & ostream, const SkipList* skip_list);
};

std::ostream & operator<< (std::ostream & ostream, const SkipList* skip_list);

#endif //DATA_STRUCTURES_SKIPLIST_H