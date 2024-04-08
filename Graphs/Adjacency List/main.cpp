#include <iostream>
#include <map>

int main() {
    std::multimap<int, std::string> myMultiMap;

    // Inserting values with duplicate keys
    myMultiMap.insert(std::make_pair(1, "apple"));
    myMultiMap.insert(std::make_pair(2, "banana"));
    myMultiMap.insert(std::make_pair(1, "orange")); // Duplicate key 1

    // Deleting entries with key 1
    auto range = myMultiMap.equal_range(1);
    myMultiMap.erase(1);

    // Iterate over the multimap after deletion
    for (const auto& pair : myMultiMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
