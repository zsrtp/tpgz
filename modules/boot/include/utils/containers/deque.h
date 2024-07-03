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

    void swap(iterator it1, iterator it2) {
        if (it1.node == nullptr || it2.node == nullptr || it1 == it2) {
            return;
        }

        Node* node1 = it1.node;
        Node* node2 = it2.node;

        // Swap the data
        T temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;

        // Update the next and prev pointers
        Node* prev1 = node1->prev;
        Node* next1 = node1->next;
        Node* prev2 = node2->prev;
        Node* next2 = node2->next;

        if (prev1 != nullptr) {
            prev1->next = node2;
        } else {
            head = node2;
        }

        if (next1 != nullptr) {
            next1->prev = node2;
        } else {
            tail = node2;
        }

        if (prev2 != nullptr) {
            prev2->next = node1;
        } else {
            head = node1;
        }

        if (next2 != nullptr) {
            next2->prev = node1;
        } else {
            tail = node1;
        }

        node1->prev = prev2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = next1;
    }

    void move(iterator from, iterator to) {
        if (from == to) {
            return;
        }

        Node* fromNode = from.node;
        Node* toNode = to.node;

        // Remove the node from its current position
        if (fromNode->prev != nullptr) {
            fromNode->prev->next = fromNode->next;
        } else {
            head = fromNode->next;
        }

        if (fromNode->next != nullptr) {
            fromNode->next->prev = fromNode->prev;
        } else {
            tail = fromNode->prev;
        }

        // Insert the node at the new position
        if (toNode != nullptr) {
            if (toNode->prev != nullptr) {
                toNode->prev->next = fromNode;
            } else {
                head = fromNode;
            }
            fromNode->prev = toNode->prev;
            fromNode->next = toNode;
            toNode->prev = fromNode;
        } else {
            // Insert at the end of the deque
            if (tail != nullptr) {
                tail->next = fromNode;
            } else {
                head = fromNode;
            }
            fromNode->prev = tail;
            fromNode->next = nullptr;
            tail = fromNode;
        }
    }

    T& at(size_t index) {
        if (index >= _size) {
            throw "Index out of range";
        }
        Node* currentNode = head;
        for (size_t i = 0; i < index; ++i) {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    const T& at(size_t index) const {
        if (index >= _size) {
            throw "Index out of range";
        }
        Node* currentNode = head;
        for (size_t i = 0; i < index; ++i) {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    T& operator[](size_t index) {
        return at(index);
    }

    const T& operator[](size_t index) const {
        return at(index);
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