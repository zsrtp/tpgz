#ifndef TPGZ_BOOT_UTILS_DEQUE_H
#define TPGZ_BOOT_UTILS_DEQUE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <atomic>
#include <iterator>
#include <concepts>
#include <type_traits>

namespace tpgz::containers {

template <typename T>
class deque {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

public:
    class iterator {
    private:
        Node* node;

    public:
        iterator(Node* pNode) : node(pNode) {}

        T& operator*() { return node->data; }

        T& operator*() const { return node->data; }

        T* operator->() { return &(node->data); }

        T* operator->() const { return &(node->data); }

        iterator& operator++() {
            node = node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            node = node->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return node == other.node; }

        bool operator!=(const iterator& other) const { return !(*this == other); }
        friend class deque;
    };

    using const_iterator = iterator;

private:
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    std::atomic<size_t> _size;

public:
    deque() : head(nullptr), tail(nullptr), _size(0) {}

    ~deque() { clear(); }

    void erase(iterator it) {
        Node* currentNode = it.node;

        if (currentNode == nullptr) {
            return;
        }

        if (currentNode == head) {
            // The iterator points to the head node
            pop_front();
            return;
        } else if (currentNode == tail) {
            // The iterator points to the tail node
            pop_back();
            return;
        }

        // A node in the middle of the deque
        Node* prevNode = currentNode->prev;
        Node* nextNode = currentNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        delete currentNode;
        --_size;
    }

    void push_front(const T& value) {
        Node* newNode = new Node{value, nullptr, nullptr};
        Node* oldHead = head;
        do {
            newNode->next = oldHead;
        } while (!std::atomic_compare_exchange_strong(&head, &oldHead, newNode));
        if (oldHead != nullptr) {
            oldHead->prev = newNode;
        }
        if (tail == nullptr) {
            tail = newNode;
        }
        ++_size;
    }

    void push_back(const T& value) {
        Node* newNode = new Node{value, nullptr, nullptr};
        Node* oldTail = tail;
        do {
            newNode->prev = oldTail;
        } while (!std::atomic_compare_exchange_strong(&tail, &oldTail, newNode));
        if (oldTail != nullptr) {
            oldTail->next = newNode;
        }
        if (head == nullptr) {
            head = newNode;
        }
        ++_size;
    }

    void pop_front() {
        Node* oldHead = head;
        if (oldHead == nullptr) {
            return;
        }
        Node* newHead = oldHead->next;
        while (!std::atomic_compare_exchange_strong(&head, &oldHead, newHead)) {
            newHead = oldHead->next;
            if (newHead == nullptr) {
                return;
            }
        }
        if (newHead != nullptr) {
            newHead->prev = nullptr;
        }
        delete oldHead;
        --_size;
        if (_size == 0) {
            tail = nullptr;
        }
    }

    void pop_back() {
        Node* oldTail = tail;
        if (oldTail == nullptr) {
            return;
        }
        Node* newTail = oldTail->prev;
        while (!std::atomic_compare_exchange_strong(&tail, &oldTail, newTail)) {
            newTail = oldTail->prev;
            if (newTail == nullptr) {
                return;
            }
        }
        if (newTail != nullptr) {
            newTail->next = nullptr;
        }
        delete oldTail;
        --_size;
        if (_size == 0) {
            head = nullptr;
        }
    }

    T& front() { return head->data; }

    T& back() { return tail->data; }

    size_t size() const { return _size.load(); }

    bool empty() const { return _size.load() == 0; }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void resize(size_t new_size) {
        while (_size > new_size) {
            pop_back();
        }
        while (_size < new_size) {
            push_back(T());
        }
    }

    void resize(size_t new_size, const T& value) {
        while (_size > new_size) {
            pop_back();
        }
        while (_size < new_size) {
            push_back(value);
        }
    }

    iterator begin() { return iterator(head); }

    iterator end() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(head); }

    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return begin(); }

    const_iterator cend() const { return end(); }
};

}  // namespace tpgz::containers

#endif