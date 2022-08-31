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
concept Function = std::is_function_v<std::remove_pointer_t<T>>;

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

    template <typename... Args>
    void dispatchAll(Args... args) requires std::invocable<T, Args...> {
        for (T* cb : callbacks) {
            cb(args...);
        }
    }

    size_t getStackSize() const { return std::distance(callbacks.begin(), callbacks.end()); }

private:
    std::deque<std::remove_pointer_t<T>*> callbacks;
};

}  // namespace events

#endif