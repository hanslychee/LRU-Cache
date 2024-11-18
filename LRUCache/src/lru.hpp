#pragma once
#include <iostream>
#include <unordered_map>
#include "intrusive_list.hpp"
#include "hashtable.hpp"

template <typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}
    void put(const Key& key, const Value& value) {
        auto* existing_entry = map_.find(key);
        if (capacity_ == 0) {
            return;
        }
        if (existing_entry != nullptr) {
            // Update the value and move the node to the front
            auto* node = *existing_entry;       // Dereference to get the Node*
            node->data.value = value;          // Update the value
            touch(node);                       // Move to the front
        }
        else {
            // Evict the least recently used item if at capacity
            if (list_.size() == capacity_) {
                evict();
            }
            // Add a new node to the front of the list
            list_.push_front({ key, value });
            auto* new_node = list_.head_node(); // Get the head node
            map_.insert(key, new_node);        // Add the Node* to the hash table
        }
    }


    Value get(const Key& key) {
        auto* entry = map_.find(key);  // Find the entry in the hash table
        if (!entry) {
            throw std::runtime_error("Key not found");
        }
        auto* node = (*entry);        // Dereference to access the Node* stored as value
        touch(node);                  // Move the node to the front
        return node->data.value;      // Return the associated value
    }

    size_t size() const {
        return list_.size();
    }

    // Implement clear method
    void clear() {
        // Clear the list
        list_.clear();

        // Clear the map
        map_.clear();
    }

    bool contains(const Key& key) {
        return map_.find(key) != nullptr;
    }

    void display() {
        for (auto it = list_.begin(); it != list_.end(); ++it) {
            std::cout << it->key << ": " << it->value << " -> ";
        }
        std::cout << "NULL\n";
    }

    void print_state() {
        std::cout << "List: ";
        for (auto it = list_.begin(); it != list_.end(); ++it) {
            std::cout << it->key << ": " << it->value << " -> ";
        }
        std::cout << "NULL\n";

        std::cout << "Map: ";
        for (auto& entry : map_) {
            if (entry.is_active) { // Check if the entry is active
                auto* node = entry.value; // This is a Node*
                std::cout << entry.key << ": " << node->data.value << " -> ";
            }
        }

        std::cout << "NULL\n";
    }



private:
    struct CacheEntry {
        Key key;
        Value value;
    };

    IntrusiveList<CacheEntry> list_;
    HashTable<Key, typename IntrusiveList<CacheEntry>::Node*> map_;
    size_t capacity_;

    void touch(typename IntrusiveList<CacheEntry>::Node* node) {
        if (node == list_.head_node()) return; // Already at the front
        list_.remove(node);                   // Remove the node from its current position
        list_.push_front(node);               // Re-add the same node at the front
        // No need to update map_ as it already points to the correct node
    }

  
    void evict() {
        // Remove the least recently used element (tail)
        if (list_.empty()) return;
        Key lru_key = list_.back().key;
        list_.pop_back();
        map_.erase(lru_key);
    }
};
