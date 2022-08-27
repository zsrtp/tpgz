#ifndef TPGZ_BOOT_HANDLERS_BASE_H
#define TPGZ_BOOT_HANDLERS_BASE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <concepts>
#include <type_traits>

namespace handler {
template <typename T>
concept Function = std::is_function_v<T>;

template <Function T>
struct CallbackNode {
    CallbackNode<T>* prev;
    CallbackNode<T>* next;
    T* elem;
};

template <Function T>
class CallbackList;

template <Function T>
class CallbackIterator {
    CallbackNode<T>* curr;

public:
    CallbackIterator(CallbackList<T>* list);
    virtual ~CallbackIterator() {}

    T* operator*() {
        if (curr != nullptr) {
            return curr->elem;
        }
        return nullptr;
    }

    CallbackIterator<T>& operator++() {
        if (curr != nullptr) {
            curr = curr->next;
        }
        return *this;
    }

    CallbackIterator<T> operator++(int) {
        CallbackIterator<T> old = *this;
        operator++();
        return old;
    }

    CallbackIterator<T>& operator--() {
        if (curr != nullptr) {
            curr = curr->prev;
        }
        return *this;
    }

    CallbackIterator<T> operator--(int) {
        CallbackIterator<T> old = *this;
        operator--();
        return old;
    }

    inline bool operator==(const CallbackIterator<T>& rhs) const { return this->curr == rhs.curr; }

    operator bool() const { return curr != nullptr && curr->elem != nullptr; }

    bool hasNext() const { return curr != nullptr && curr->next != nullptr; }

    bool hasPrev() const { return curr != nullptr && curr->prev != nullptr; }
};

template <Function T>
class CallbackConstIterator {
    const CallbackNode<T>* curr;

public:
    CallbackConstIterator(const CallbackList<T>* list);
    virtual ~CallbackConstIterator() {}

    const T* operator*() const {
        if (curr != nullptr) {
            return curr->elem;
        }
        return nullptr;
    }

    CallbackConstIterator<T>& operator++() {
        if (curr != nullptr) {
            curr = curr->next;
        }
        return *this;
    }

    CallbackConstIterator<T> operator++(int) {
        auto old = *this;
        operator++();
        return old;
    }

    CallbackConstIterator<T>& operator--() {
        if (curr != nullptr) {
            curr = curr->prev;
        }
        return *this;
    }

    CallbackConstIterator<T> operator--(int) {
        auto old = *this;
        operator--();
        return old;
    }

    inline bool operator==(const CallbackConstIterator<T>& rhs) const {
        return this->curr == rhs.curr;
    }

    operator bool() const { return curr != nullptr && curr->elem != nullptr; }

    bool hasNext() const { return curr != nullptr && curr->next != nullptr; }

    bool hasPrev() const { return curr != nullptr && curr->prev != nullptr; }
};

template <Function T>
class CallbackList {
public:
    CallbackList() {}
    virtual ~CallbackList() {
        CallbackNode<T>* item = getLast();
        while (item != nullptr) {
            CallbackNode<T>* prev = item->prev;
            delete item;
            item = prev;
        }
    }

    void push(T* cb) {
        if (cb == nullptr) {
            return;
        }
        CallbackNode<T>* item = new CallbackNode<T>;
        CallbackNode<T>* last = getLast();
        item->prev = last;
        item->next = nullptr;
        item->elem = cb;
        if (last == nullptr) {
            first = item;
            return;
        }
        item->prev = last;
        last->next = item;
    }

    bool remove(T* cb) {
        CallbackNode<T>* item = first;
        while (item != nullptr && item->elem != cb) {
            item = item->next;
        }
        if (item != nullptr) {
            CallbackNode<T>* prev = item->prev;
            CallbackNode<T>* next = item->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next != nullptr) {
                next->prev = prev;
            }
            if (first == item) {
                first = next;
            }
            delete item;
            return true;
        }
        return false;
    }

    CallbackIterator<T> begin() { return CallbackIterator<T>(this); }
    CallbackConstIterator<T> begin() const { return CallbackConstIterator<T>(this); }

    CallbackIterator<T> end() {
        auto it = CallbackIterator<T>(this);
        while (it.hasNext()) {
            ++it;
        }
        return it;
    }
    CallbackConstIterator<T> end() const {
        auto it = CallbackConstIterator<T>(this);
        while (it.hasNext()) {
            ++it;
        }
        return it;
    }

private:
    CallbackNode<T>* first;

    CallbackNode<T>* getLast() const {
        if (first == nullptr) {
            return nullptr;
        }
        CallbackNode<T>* item = first;
        while (item->next != nullptr) {
            item = item->next;
        }
        return item;
    }

public:
    friend class CallbackIterator<T>;
    friend class CallbackConstIterator<T>;
};

template <Function T>
CallbackIterator<T>::CallbackIterator(CallbackList<T>* list) {
    curr = list->first;
}

template <Function T>
CallbackConstIterator<T>::CallbackConstIterator(const CallbackList<T>* list) {
    curr = list->first;
}

template <Function T>
class HandlerBase {
public:
    HandlerBase() {}
    virtual ~HandlerBase() {}

    void addHandler(T* handler) { callbacks.push(handler); }

    bool removeHandler(T* handler) { return callbacks.remove(handler); }
    void handleAll(void* param) {
        for (auto it = callbacks.begin(); it; ++it) {
            T* handler = *it;
            handle(handler, param);
        }
    }

    size_t getStackSize() const {
        size_t count = 0;
        for (auto it = callbacks.begin(); it; ++it) {
            ++count;
        }
        return count;
    }

protected:
    virtual void handle(T* handler, void* param) = 0;

private:
    CallbackList<T> callbacks;
};

}  // namespace handler

#endif