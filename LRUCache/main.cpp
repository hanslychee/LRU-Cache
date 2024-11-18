#include "src/hashtable.hpp"
#include "src/intrusive_list.hpp"
#include "src/lru.hpp"
#include <iostream>

void testHashtable();
void testLRUCache();
void testIntrusiveList();

int main() {
    //testHashtable();
    //testIntrusiveList();
    testLRUCache();
    return 0;
}

void testHashtable() {
    HashTable<int, std::string> table;

    // Insert some key-value pairs
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    // Find and print the values for keys
    std::string* result = table.find(1);
    if (result) {
        std::cout << "Key 1 found with value: " << *result << std::endl;
    }
    else {
        std::cout << "Key 1 not found" << std::endl;
    }

    result = table.find(2);
    if (result) {
        std::cout << "Key 2 found with value: " << *result << std::endl;
    }
    else {
        std::cout << "Key 2 not found" << std::endl;
    }

    // Erase a key and test the find method again
    table.erase(2);
    result = table.find(2);
    if (result) {
        std::cout << "Key 2 found with value: " << *result << std::endl;
    }
    else {
        std::cout << "Key 2 not found after erase" << std::endl;
    }

    // Print the size of the hash table
    std::cout << "Size of table: " << table.size() << std::endl;

    // Clear the table and verify the size
    table.clear();
    std::cout << "Size of table after clear: " << table.size() << std::endl;
}


void testIntrusiveList() {
    IntrusiveList<int> list;

    // Test push_front
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    // Verify the front and back values
    assert(list.front() == 3); // 3 should be at the front
    assert(list.back() == 1);  // 1 should be at the back

    // Verify the size
    assert(list.size() == 3);  // The list should have 3 elements

    // Test iteration
    int expected[] = { 3, 2, 1 };
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        assert(*it == expected[i]); // Check if the iteration returns the correct values
        i++;
    }

    // Test pop_back
    list.pop_back();  // This should remove the last element (1)
    assert(list.back() == 2);  // 2 should now be at the back
    assert(list.size() == 2);  // The list should have 2 elements

    // Test clear
    list.clear();
    assert(list.empty()); // The list should now be empty
    assert(list.size() == 0); // The size should be 0

    std::cout << "All tests passed!" << std::endl;
}

void testLRUCache() {
    LRUCache<int, std::string> cache(3); // Capacity = 3

    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");
    cache.display();

    cache.get(2); // Access key 2
    cache.display();

    cache.put(4, "Four"); // Evicts key 1 (Least Recently Used)
    cache.display();

    try {
        std::cout << cache.get(1) << "\n"; // Key 1 was evicted
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

}