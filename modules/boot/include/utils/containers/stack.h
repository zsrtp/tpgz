#ifndef TPGZ_BOOT_UTILS_STACK_H
#define TPGZ_BOOT_UTILS_STACK_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <atomic>
#include <iterator>
#include <concepts>
#include <type_traits>

namespace tpgz::containers {

template <typename T>
class stack {
private:
    struct Node {
        T data;
        Node* next;
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

        bool operator==(const iterator& other) const { return node == other.node; }

        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

private:
    std::atomic<Node*> top;

public:
    stack() : top(nullptr) {}

    ~stack() { clear(); }

    void erase(iterator it) {
        Node* currentTop = top.load();
        Node* previousNode = nullptr;

        while (currentTop != nullptr) {
            if (currentTop == it.node) {
                if (previousNode == nullptr) {
                    // The top node matches the iterator
                    std::atomic_compare_exchange_strong(&top, &currentTop, currentTop->next);
                    delete currentTop;
                    currentTop = top.load();
                } else {
                    // A node in the middle of the stack matches the iterator
                    previousNode->next = currentTop->next;
                    delete currentTop;
                    currentTop = previousNode->next;
                }
                return;
            } else {
                previousNode = currentTop;
                currentTop = currentTop->next;
            }
        }
    }

    void push(const T& value) {
        Node* newNode = new Node{value, nullptr};
        Node* oldTop = top.load();
        do {
            newNode->next = oldTop;
        } while (!std::atomic_compare_exchange_strong(&top, &oldTop, newNode));
    }

    void pop() {
        Node* oldTop = top.load();
        while (oldTop != nullptr &&
               !std::atomic_compare_exchange_strong(&top, &oldTop, oldTop->next)) {
            oldTop = top.load();
        }
        if (oldTop != nullptr) {
            delete oldTop;
        }
    }

    bool empty() const { return top.load() == nullptr; }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    size_t size() const {
        Node* currentTop = top.load();
        size_t count = 0;
        while (currentTop != nullptr) {
            currentTop = currentTop->next;
            ++count;
        }
        return count;
    }

    iterator begin() { return iterator(top.load()); }

    iterator end() { return iterator(nullptr); }
};

}  // namespace tpgz::containers

#endif