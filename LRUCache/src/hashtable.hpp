// hashtable.hpp

#pragma once

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>  // for std::vector
#include <iostream> // for debugging

template <typename Key, typename Value>
class HashTable {
public:
    // Define Entry type inside the class template
    struct Entry {
        Key key;
        Value value;
        bool is_active;
    };

    // Iterator class
    class Iterator {
    public:
        Iterator(std::vector<Entry*>& table, size_t index)
            : table_(table), index_(index) {
            moveToNextActive();  // Move to the first active element
        }

        bool operator!=(const Iterator& other) const {
            return index_ != other.index_;
        }

        typename HashTable<Key, Value>::Entry& operator*() {
            return *table_[index_];
        }

        Iterator& operator++() {
            ++index_;
            moveToNextActive();
            return *this;
        }

    private:
        void moveToNextActive() {
            // Move to the next active entry in the table
            while (index_ < table_.size() && (!table_[index_] || !table_[index_]->is_active)) {
                ++index_;
            }
        }

        std::vector<Entry*>& table_;
        size_t index_;
    };

    // Constructor
    HashTable(size_t initial_capacity = 16);

    bool insert(const Key& key, const Value& value);
    bool erase(const Key& key);
    Value* find(const Key& key); // Return pointer instead of optional

    size_t size() const;
    void clear();

    // Provide begin and end methods for iteration
    Iterator begin() {
        return Iterator(table_, 0);
    }

    Iterator end() {
        return Iterator(table_, table_.size());
    }

private:
    std::vector<Entry*> table_; // A vector of pointers to Entry objects
    size_t num_elements_;
    size_t capacity_;

    size_t hash(const Key& key) const;
    void rehash();
};

// Constructor
template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t initial_capacity)
    : table_(initial_capacity, nullptr), num_elements_(0), capacity_(initial_capacity) {
}

// Insert method
template <typename Key, typename Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {
    if (num_elements_ > capacity_ / 2) {
        rehash();
    }
    size_t idx = hash(key) % capacity_;
    for (size_t i = 0; i < capacity_; ++i) {
        Entry*& entry = table_[(idx + i) % capacity_];
        if (!entry || !entry->is_active || entry->key == key) {
            if (!entry) entry = new Entry{ key, value, true };
            else entry->value = value;  // Update the value if key already exists
            ++num_elements_;
            return true;
        }
    }
    return false;
}

// Erase method
template <typename Key, typename Value>
bool HashTable<Key, Value>::erase(const Key& key) {
    size_t idx = hash(key) % capacity_;
    for (size_t i = 0; i < capacity_; ++i) {
        Entry*& entry = table_[(idx + i) % capacity_];
        if (entry && entry->is_active && entry->key == key) {
            entry->is_active = false;
            --num_elements_;
            return true;
        }
    }
    return false;
}

// Find method
template <typename Key, typename Value>
Value* HashTable<Key, Value>::find(const Key& key) {
    size_t idx = hash(key) % capacity_;
    for (size_t i = 0; i < capacity_; ++i) {
        Entry*& entry = table_[(idx + i) % capacity_];
        if (entry && entry->is_active && entry->key == key) {
            return &entry->value;  // Return pointer to the value
        }
    }
    return nullptr;  // Return nullptr if key is not found
}

// Size method
template <typename Key, typename Value>
size_t HashTable<Key, Value>::size() const {
    return num_elements_;
}

// Clear method
template <typename Key, typename Value>
void HashTable<Key, Value>::clear() {
    for (size_t i = 0; i < capacity_; ++i) {
        delete table_[i];  // Clean up dynamically allocated memory
    }
    table_.clear();
    table_.resize(capacity_, nullptr);
    num_elements_ = 0;
}

// Hash function
template <typename Key, typename Value>
size_t HashTable<Key, Value>::hash(const Key& key) const {
    return std::hash<Key>{}(key);
}

// Rehash function
template <typename Key, typename Value>
void HashTable<Key, Value>::rehash() {
    capacity_ *= 2;
    std::vector<Entry*> new_table(capacity_, nullptr);
    for (size_t i = 0; i < capacity_ / 2; ++i) {
        if (table_[i]) {
            size_t idx = hash(table_[i]->key) % capacity_;
            for (size_t j = 0; j < capacity_; ++j) {
                if (!new_table[(idx + j) % capacity_]) {
                    new_table[(idx + j) % capacity_] = table_[i];
                    break;
                }
            }
        }
    }
    table_ = std::move(new_table);
}

#endif // HASHTABLE_HPP
