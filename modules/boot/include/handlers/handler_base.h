#ifndef TPGZ_BOOT_HANDLERS_BASE_H
#define TPGZ_BOOT_HANDLERS_BASE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>

namespace handler {
template <typename T>
struct CallbackNode {
    CallbackNode<T>* prev;
    CallbackNode<T>* next;
    T* elem;
};

template <typename T>
class CallbackList;

template <typename T>
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

    CallbackIterator& operator++() {
        if (curr != nullptr) {
            curr = curr->next;
        }
        return *this;
    }

    CallbackIterator operator++(int) {
        CallbackIterator old = *this;
        operator++();
        return old;
    }

    CallbackIterator& operator--() {
        if (curr != nullptr) {
            curr = curr->prev;
        }
        return *this;
    }

    CallbackIterator operator--(int) {
        CallbackIterator old = *this;
        operator--();
        return old;
    }
};

template <typename T>
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
        item->prev = first;
        item->next = nullptr;
        item->elem = cb;
        CallbackNode<T>* last = getLast();
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
            delete item;
            return true;
        }
        return false;
    }

    CallbackIterator<T> iter() { return CallbackIterator<T>(this); }

private:
    CallbackNode<T>* first;

    CallbackNode<T>* getLast() {
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
};

template <typename T>
CallbackIterator<T>::CallbackIterator(CallbackList<T>* list) {
    curr = list->first;
}

template <typename T>
class HandlerBase {
public:
    HandlerBase() {}
    virtual ~HandlerBase() {}

    void addHandler(T* handler) { callbacks.push(handler); }

    bool removeHandler(T* handler) { return callbacks.remove(handler); }
    void handleAll(void* param) {
        CallbackIterator<T> it = callbacks.iter();
        for (CallbackIterator<T> it = callbacks.iter(); *it != nullptr; ++it) {
            T* handler = *it;
            handle(handler, param);
        }
    }

protected:
    virtual void handle(T* handler, void* param) = 0;

private:
    CallbackList<T> callbacks;
};

}  // namespace handler

#endif