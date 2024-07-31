#include "SkipList.h"

SkipList::SkipList(const int& rLimit, const int& maxLevel) : rLimit(rLimit), level(1), size(0)
{
    head = new SkipList_Node{-1, new SkipList_Node*[(this->maxLevel = maxLevel < 0 ? 1 : maxLevel)]};
    memset(head->next, 0, sizeof (SkipList_Node) * this->maxLevel);
}

int SkipList::get_rNumber() const
{
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_real_distribution<double> distribution(0, rLimit);

    int rLevel;
    for(rLevel = 1; distribution(gen) < rLimit && rLevel < maxLevel; rLevel++) {}

    return rLevel;
}

SkipList& SkipList::insertKey(const int& key)
{
    const int rLimit = get_rNumber();
    SkipList_Node * curr = head;
    auto ** updateList = new SkipList_Node*[rLimit];

    if(rLimit > level)
        level = rLimit;

    for(int i = rLimit - 1; i >= 0; i--)
    {
        while(curr->next[i] && curr->next[i]->value < key)
            curr = curr->next[i];

        updateList[i] = curr;
    }

    if(curr->next[0] && curr->next[0]->value == key)
        return *this;

    auto * newNode = new SkipList_Node{key};

    for(int i = rLimit - 1; i >= 0; i--)
    {
        newNode->next[i] = updateList[i]->next[i];
        updateList[i]->next[i] = newNode;
    }

    size++;

    return *this;
}

std::ostream & operator<< (std::ostream & ostream, const SkipList* skip_list)
{
    ostream << "Size: " << skip_list->size << '\n';

    for(int i = skip_list->level - 1; i >= 0; i--)
    {
        const SkipList::SkipList_Node * curr = skip_list->head->next[i];
        ostream << "Level: " << i + 1 << '\n';
        while(curr)
        {
            ostream << curr->value << ' ';
            curr = curr->next[i];
        }
    }

    return ostream;
}