#ifndef TPGZ_BOOT_LISTENERS_BASE_H
#define TPGZ_BOOT_LISTENERS_BASE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <concepts>
#include <type_traits>
#include <deque>
#include <algorithm>

namespace events {
template <typename T>
concept Function = std::is_function_v<T>;

template <Function T>
class ListenerBase {
public:
    ListenerBase() {}
    virtual ~ListenerBase() {}

    void addListener(T* listener) { callbacks.push_back(listener); }

    bool removeListener(T* listener) {
        auto it = std::find(callbacks.begin(), callbacks.end(), listener);
        if (it == callbacks.end()) {
            return false;
        }
        callbacks.erase(it);
        return true;
    }

    void dispatchAll(void* param) {
        for (auto cb : callbacks) {
            dispatch(cb, param);
        }
    }

    size_t getStackSize() const { return std::distance(callbacks.begin(), callbacks.end()); }

protected:
    virtual void dispatch(T* listener, void* param) = 0;

private:
    std::deque<T*> callbacks;
};

}  // namespace events

#endif