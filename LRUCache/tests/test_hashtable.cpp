#include "../src/hashtable.hpp"

#include <gtest/gtest.h>

TEST(HashTableTest, InsertAndFind) {
    HashTable<int, std::string> table;
    EXPECT_TRUE(table.insert(1, "one"));
    EXPECT_TRUE(table.insert(2, "two"));

    // Testing the find method, which now returns a pointer
    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(*result, "one");  // Dereference the pointer to compare the value

    result = table.find(2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "two");
}

TEST(HashTableTest, Erase) {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_TRUE(table.erase(1));
    EXPECT_EQ(table.find(1), nullptr);  // Should return nullptr after erase

    EXPECT_TRUE(table.erase(2));
    EXPECT_EQ(table.find(2), nullptr);  // Should return nullptr after erase
}

TEST(HashTableTest, Clear) {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    table.clear();
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find(1), nullptr);  // Should return nullptr after clear
    EXPECT_EQ(table.find(2), nullptr);  // Should return nullptr after clear
}

TEST(HashTableTest, InsertWithExistingKey) {
    HashTable<int, std::string> table;
    table.insert(1, "one");

    // Insert a new value for the existing key
    EXPECT_TRUE(table.insert(1, "updated_one"));

    // Verify the updated value
    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "updated_one");
}

TEST(HashTableTest, FindNonExistentKey) {
    HashTable<int, std::string> table;
    table.insert(1, "one");

    // Find a non-existent key (should return nullptr)
    std::string* result = table.find(2);
    EXPECT_EQ(result, nullptr);
}

TEST(HashTableTest, InsertAndSize) {
    HashTable<int, std::string> table;

    EXPECT_TRUE(table.insert(1, "one"));
    EXPECT_TRUE(table.insert(2, "two"));

    // Check size after inserts
    EXPECT_EQ(table.size(), 2);
}

TEST(HashTableTest, EraseNonExistentKey) {
    HashTable<int, std::string> table;
    table.insert(1, "one");

    // Erase a non-existent key
    EXPECT_FALSE(table.erase(2));  // Should return false
}

TEST(HashTableTest, ClearEmptyTable) {
    HashTable<int, std::string> table;

    // Clear an empty table
    table.clear();

    // Verify that the table is still empty
    EXPECT_EQ(table.size(), 0);
}

TEST(HashTableTest, InsertAndClear) {
    HashTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    // Clear the table
    table.clear();

    // Ensure the table is empty
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
}

TEST(HashTableTest, SizeAfterErase) {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    // Erase one element and check size
    EXPECT_TRUE(table.erase(1));
    EXPECT_EQ(table.size(), 1);  // Size should be 1

    // Erase another element and check size
    EXPECT_TRUE(table.erase(2));
    EXPECT_EQ(table.size(), 0);  // Size should be 0
}

TEST(HashTableTest, InsertMultipleKeys) {
    HashTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "one");

    result = table.find(2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "two");

    result = table.find(3);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "three");
}

TEST(HashTableTest, ClearAfterInsert) {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    // Call clear() and verify the table is empty
    table.clear();
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
}


TEST(HashTableTest, InsertZeroElements) {
    HashTable<int, std::string> table;

    // Verify that the table is empty after no insertions
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find(1), nullptr);
}

TEST(HashTableTest, InsertDuplicateKeys) {
    HashTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(1, "duplicate_one");

    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "duplicate_one");  // The value should be updated
}

TEST(HashTableTest, InsertMultipleKeysWithCollisions) {
    HashTable<int, std::string> table;

    // Inserting keys that will likely hash to the same bucket (if the hash function is simple)
    table.insert(1, "one");
    table.insert(11, "eleven");  // Assuming simple modulo hash function

    // Verify that both entries exist
    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "one");

    result = table.find(11);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "eleven");
}

TEST(HashTableTest, InsertEmptyString) {
    HashTable<int, std::string> table;

    // Insert an empty string as a value
    EXPECT_TRUE(table.insert(1, ""));

    // Verify that the empty string is stored correctly
    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "");
}

TEST(HashTableTest, EraseAllElements) {
    HashTable<int, std::string> table;

    // Insert multiple elements
    table.insert(1, "one");
    table.insert(2, "two");

    // Erase all elements one by one
    EXPECT_TRUE(table.erase(1));
    EXPECT_TRUE(table.erase(2));

    // Ensure the table is empty
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
}

TEST(HashTableTest, FindAfterClear) {
    HashTable<int, std::string> table;

    // Insert elements and clear the table
    table.insert(1, "one");
    table.insert(2, "two");
    table.clear();

    // Verify that find returns nullptr after clear
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
}

TEST(HashTableTest, InsertWithCaseSensitiveStrings) {
    HashTable<int, std::string> table;

    // Insert two strings that only differ in case
    EXPECT_TRUE(table.insert(1, "Hello"));
    EXPECT_TRUE(table.insert(2, "hello"));

    // Verify that they are stored correctly
    std::string* result = table.find(1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "Hello");

    result = table.find(2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "hello");
}

TEST(HashTableTest, InsertLargeNumberOfElements) {
    HashTable<int, std::string> table;

    // Insert a large number of elements
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(table.insert(i, "value" + std::to_string(i)));
    }

    // Verify size and a few key-value pairs
    EXPECT_EQ(table.size(), 1000);
    std::string* result = table.find(500);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "value500");
}


TEST(HashTableTest, SizeAfterMultipleInsertsAndErases) {
    HashTable<int, std::string> table;

    // Insert 5 elements
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(5, "five");

    // Erase 2 elements
    table.erase(2);
    table.erase(4);

    // Verify size is correct
    EXPECT_EQ(table.size(), 3);
}

TEST(HashTableTest, EraseAndFindNonExistentKey) {
    HashTable<int, std::string> table;

    // Insert elements
    table.insert(1, "one");
    table.insert(2, "two");

    // Erase a key and then attempt to find it
    EXPECT_TRUE(table.erase(1));
    EXPECT_EQ(table.find(1), nullptr);

    // Verify that other elements still exist
    std::string* result = table.find(2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "two");
}




