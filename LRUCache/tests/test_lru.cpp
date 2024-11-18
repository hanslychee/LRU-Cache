#include "../src/lru.hpp"  // Include the correct header file
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Test storing and retrieving from the cache
TEST(LRUCacheTest, StoreAndRetrieve) {
    LRUCache<int, std::string> cache(2);  // Capacity = 2

    // Add first item
    cache.put(1, "One");
    EXPECT_EQ(cache.get(1), "One");

    // Add second item
    cache.put(2, "Two");
    EXPECT_EQ(cache.get(2), "Two");

    // Add third item, evicting the first one (LRU)
    cache.put(3, "Three");
    EXPECT_THROW(cache.get(1), std::runtime_error);  // 1 should be evicted
    EXPECT_EQ(cache.get(2), "Two");
    EXPECT_EQ(cache.get(3), "Three");
}

// Test eviction behavior
TEST(LRUCacheTest, EvictionPolicy) {
    LRUCache<int, std::string> cache(3);  // Capacity = 3

    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");

    // Access an earlier entry to make it most recently used
    EXPECT_EQ(cache.get(1), "One");

    // Add a new entry, evicting the least recently used (2)
    cache.put(4, "Four");

    //cache.print_state();

    EXPECT_THROW(cache.get(2), std::runtime_error);  // 2 should be evicted
    EXPECT_EQ(cache.get(1), "One");                 // 1 should still be present
    EXPECT_EQ(cache.get(3), "Three");
    EXPECT_EQ(cache.get(4), "Four");
}

// Test cache capacity edge case
TEST(LRUCacheTest, CapacityEdgeCase) {
    LRUCache<int, std::string> cache(1);  // Capacity = 1

    // Add an item
    cache.put(1, "One");
    EXPECT_EQ(cache.get(1), "One");

    // Add another item, evicting the first one
    cache.put(2, "Two");
    EXPECT_THROW(cache.get(1), std::runtime_error);  // 1 should be evicted
    EXPECT_EQ(cache.get(2), "Two");
}

// Test contains functionality
TEST(LRUCacheTest, ContainsFunctionality) {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "One");
    EXPECT_TRUE(cache.contains(1));
    EXPECT_FALSE(cache.contains(2));

    cache.put(2, "Two");
    EXPECT_TRUE(cache.contains(2));

    // Evict 1 by adding another element
    cache.put(3, "Three");
    EXPECT_FALSE(cache.contains(1));  // 1 should be evicted
    EXPECT_TRUE(cache.contains(3));
}

// Test display functionality
TEST(LRUCacheTest, Display) {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "One");
    cache.put(2, "Two");

    testing::internal::CaptureStdout();
    cache.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "2: Two -> 1: One -> NULL\n");
}

// Test when attempting to get a non-existent key
TEST(LRUCacheTest, GetNonExistentKey) {
    LRUCache<int, std::string> cache(2);

    EXPECT_THROW(cache.get(1), std::runtime_error);  // Key does not exist
}

// Test adding duplicate keys
TEST(LRUCacheTest, AddDuplicateKey) {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "One");
    cache.put(1, "UpdatedOne");  // Update the existing key

    EXPECT_EQ(cache.get(1), "UpdatedOne");
    EXPECT_EQ(cache.size(), 1);
}

TEST(LRUCacheTest, LargeCapacity) {
    LRUCache<int, std::string> cache(1000);  // Large capacity

    for (int i = 1; i <= 1000; ++i) {
        cache.put(i, "Value" + std::to_string(i));
    }

    for (int i = 1; i <= 1000; ++i) {
        EXPECT_EQ(cache.get(i), "Value" + std::to_string(i));
    }
}

TEST(LRUCacheTest, ZeroCapacity) {
    LRUCache<int, std::string> cache(0);  // Zero capacity

    cache.put(1, "One");
    EXPECT_THROW(cache.get(1), std::runtime_error);  // No items can be stored
}

TEST(LRUCacheTest, UpdateExistingKey) {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "One");
    cache.put(2, "Two");

    // Update key 1
    cache.put(1, "UpdatedOne");
    EXPECT_EQ(cache.get(1), "UpdatedOne");
    EXPECT_EQ(cache.get(2), "Two");
}

TEST(LRUCacheTest, CacheSize) {
    LRUCache<int, std::string> cache(3);

    EXPECT_EQ(cache.size(), 0);

    cache.put(1, "One");
    EXPECT_EQ(cache.size(), 1);

    cache.put(2, "Two");
    EXPECT_EQ(cache.size(), 2);

    cache.put(3, "Three");
    EXPECT_EQ(cache.size(), 3);

    // Adding one more item should evict the least recently used item
    cache.put(4, "Four");
    EXPECT_EQ(cache.size(), 3);
}

TEST(LRUCacheTest, AccessOrder) {
    LRUCache<int, std::string> cache(3);

    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");

    // Access key 1 to update its LRU status
    EXPECT_EQ(cache.get(1), "One");

    // Add another item, evicting the least recently used (2)
    cache.put(4, "Four");

    EXPECT_THROW(cache.get(2), std::runtime_error);  // 2 should be evicted
    EXPECT_EQ(cache.get(1), "One");
    EXPECT_EQ(cache.get(3), "Three");
    EXPECT_EQ(cache.get(4), "Four");
}

TEST(LRUCacheTest, ClearCache) {
    LRUCache<int, std::string> cache(3);

    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");

    EXPECT_EQ(cache.size(), 3);

    cache.clear();
    EXPECT_EQ(cache.size(), 0);
    EXPECT_THROW(cache.get(1), std::runtime_error);
    EXPECT_THROW(cache.get(2), std::runtime_error);
    EXPECT_THROW(cache.get(3), std::runtime_error);
}

TEST(LRUCacheTest, NonStringValues) {
    LRUCache<int, int> cache(2);

    cache.put(1, 100);
    cache.put(2, 200);

    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);

    cache.put(3, 300);  // Evicts key 1
    EXPECT_THROW(cache.get(1), std::runtime_error);
    EXPECT_EQ(cache.get(3), 300);
}

TEST(LRUCacheTest, RepeatedKeyInserts) {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "One");
    cache.put(1, "UpdatedOne");
    cache.put(1, "FinalOne");

    EXPECT_EQ(cache.get(1), "FinalOne");
    EXPECT_EQ(cache.size(), 1);  // Size should remain 1
}

TEST(LRUCacheTest, InvalidGet) {
    LRUCache<int, std::string> cache(2);

    EXPECT_THROW(cache.get(1), std::runtime_error);  // Key does not exist
    cache.put(1, "One");
    EXPECT_NO_THROW(cache.get(1));  // Key exists
}