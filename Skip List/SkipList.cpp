#include "SkipList.h"

SkipList::SkipList(const float& rLimit, const int& maxLevel) : rLimit(rLimit), level(1), size(0)
{
    head = new SkipList_Node{-1, new SkipList_Node*[(this->maxLevel = maxLevel < 0 ? 1 : maxLevel)]};
    memset(head->next, 0, sizeof (SkipList_Node*) * this->maxLevel);
}

SkipList::SkipList_Node** SkipList::get_update_list_node(const int& key) const
{
    SkipList_Node * curr = head;
    auto ** updateList = new SkipList_Node*[level];

    for(int i = level - 1; i >= 0; i--)
    {
        while(curr->next[i] && curr->next[i]->value < key)
            curr = curr->next[i];

        updateList[i] = curr;
    }

    return updateList;
}

bool SkipList::keyExist(const int& key) const
{
    SkipList_Node ** result = get_update_list_node(key);
    const SkipList_Node * nextNode = result[0]->next[0];

    delete[] result;

    return nextNode && nextNode->value == key;
}

SkipList& SkipList::deleteKey(const int& key)
{
    SkipList_Node ** updateList = get_update_list_node(key);

    if(updateList[0]->next[0] && updateList[0]->next[0]->value == key)
    {
        const SkipList_Node * exactNode = updateList[0]->next[0];
        for(int i = 0; i < level; i++)
        {
            if(const SkipList_Node * node_in_array = updateList[i];
                node_in_array->next[i] && node_in_array->next[i]->value == key)
                node_in_array->next[i] = node_in_array->next[i]->next[i];
        }

        delete exactNode;

        for(int i = level - 1; i >= 0; i--)
            if(!head->next[i])
                level--;

        size--;
    }

    delete[] updateList;

    return *this;
}


int SkipList::get_rNumber() const
{
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_real_distribution<double> distribution(0, 1);

    int rLevel;
    for(rLevel = 1;distribution(gen) < rLimit && rLevel < maxLevel; rLevel++) {}

    return rLevel;
}

SkipList& SkipList::insertKey(const int& key)
{
    const int rLimit = get_rNumber();

    if(rLimit > level)
        level = rLimit;

    SkipList_Node ** updateList = get_update_list_node(key);

    if(updateList[0]->next[0] && updateList[0]->next[0]->value == key)
        return *this;

    auto * newNode = new SkipList_Node{key, new SkipList_Node*[rLimit]};

    for(int i = rLimit - 1; i >= 0; i--)
    {
        newNode->next[i] = updateList[i]->next[i];
        updateList[i]->next[i] = newNode;
    }

    size++;

    delete[] updateList;

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

        ostream << '\n';
    }

    return ostream;
}