// tests/test_intrusive_list.cpp
#include "../src/intrusive_list.hpp"
#include <gtest/gtest.h>

TEST(IntrusiveListTest, PushFront) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.size(), 3);
}

TEST(IntrusiveListTest, PopBack) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    list.pop_back();
    EXPECT_EQ(list.back(), 3);
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(IntrusiveListTest, Clear) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);

    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(IntrusiveListTest, Iteration) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    int expected[] = { 3, 2, 1 };
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected[i++]);
    }
}

TEST(IntrusiveListTest, ClearOnNonEmptyList) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);

    // Clear the list and ensure it's empty
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(IntrusiveListTest, InsertionAfterClear) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);

    list.clear();

    // Insert new elements after clear
    list.push_front(3);
    list.push_front(4);

    EXPECT_EQ(list.front(), 4);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 2);
}

TEST(IntrusiveListTest, IterationOnEmptyList) {
    IntrusiveList<int> list;

    // Verify iteration on an empty list
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ++count;
    }

    EXPECT_EQ(count, 0);  // No elements to iterate over
}

TEST(IntrusiveListTest, PushFrontAfterClear) {
    IntrusiveList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.clear();

    // Verify the list is empty after clear
    EXPECT_TRUE(list.empty());

    // Push new elements and verify list again
    list.push_front(3);
    list.push_front(4);
    EXPECT_EQ(list.front(), 4);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 2);
}

TEST(IntrusiveListTest, FrontAndBackOneElement) {
    IntrusiveList<int> list;
    list.push_front(1);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.size(), 1);
}

TEST(IntrusiveListTest, CopyConstructorEmptyList) {
    IntrusiveList<int> list;
    IntrusiveList<int> copied_list = list;

    // Ensure the copied list is also empty
    EXPECT_TRUE(copied_list.empty());
    EXPECT_EQ(copied_list.size(), 0);
}

TEST(IntrusiveListTest, AssignmentOperatorEmptyList) {
    IntrusiveList<int> list;
    IntrusiveList<int> assigned_list;

    assigned_list = list;

    // Ensure the assigned list is empty
    EXPECT_TRUE(assigned_list.empty());
    EXPECT_EQ(assigned_list.size(), 0);
}

TEST(IntrusiveListTest, InsertAndClearMultipleTimes) {
    IntrusiveList<int> list;

    // Insert and clear multiple times
    list.push_front(1);
    list.push_front(2);
    list.clear();
    EXPECT_TRUE(list.empty());

    list.push_front(3);
    list.push_front(4);
    list.clear();
    EXPECT_TRUE(list.empty());

    list.push_front(5);
    list.push_front(6);
    EXPECT_EQ(list.size(), 2);
}





