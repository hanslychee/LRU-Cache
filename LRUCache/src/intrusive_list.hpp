//intrusive_list.hpp

#pragma once

#ifndef INTRUSIVE_LIST_HPP
#define INTRUSIVE_LIST_HPP

#include <iterator>
#include <cassert>

template <typename T>
class IntrusiveList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head_node() const {
        return head;
    }

    class Iterator {
    public:
        explicit Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }
        T* operator->() { return &current->data; } // Overload -> for member access
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        Node* current;
    };

    IntrusiveList() : head(nullptr), tail(nullptr), size_(0) {}
    ~IntrusiveList() { clear(); }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        if (head) {
            head->prev = new_node;
        }
        else {
            tail = new_node;
        }
        head = new_node;
        ++size_;
    }

    void push_front(Node* node) {
        if (!node) return;

        // Reset links in the existing node
        node->prev = nullptr;
        node->next = head;

        if (head) {
            head->prev = node;
        }
        else {
            tail = node; // If the list was empty, the new node becomes the tail
        }

        head = node;
        ++size_;
    }


    void pop_back() {
        if (!tail) return;
        Node* old_tail = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete old_tail;
        --size_;
    }

    void remove(Node* node) {
        if (!node) return;

        if (node->prev) {
            node->prev->next = node->next;
        }
        else {
            head = node->next; // Node is the head
        }

        if (node->next) {
            node->next->prev = node->prev;
        }
        else {
            tail = node->prev; // Node is the tail
        }

        node->next = nullptr;
        node->prev = nullptr;
        --size_;
    }



    T& front() const { return head->data; }
    T& back() const { return tail->data; }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    typename IntrusiveList<T>::Node* get_previous_to_end() const {
    return tail; // Assuming `tail` points to the last node in the list
}

private:
    Node* head;
    Node* tail;
    size_t size_;
};

#endif // INTRUSIVE_LIST_HPP
