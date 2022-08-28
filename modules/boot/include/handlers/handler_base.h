#ifndef TPGZ_BOOT_HANDLERS_BASE_H
#define TPGZ_BOOT_HANDLERS_BASE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <concepts>
#include <type_traits>
#include <deque>
#include <algorithm>

namespace handler {
template <typename T>
concept Function = std::is_function_v<T>;

template <Function T>
class HandlerBase {
public:
    HandlerBase() {}
    virtual ~HandlerBase() {}

    void addHandler(T* handler) { callbacks.push_back(handler); }

    bool removeHandler(T* handler) {
        auto it = std::find(callbacks.begin(), callbacks.end(), handler);
        if (it == callbacks.end()) {
            return false;
        }
        callbacks.erase(it);
        return true;
    }

    void handleAll(void* param) {
        for (auto handler : callbacks) {
            handle(handler, param);
        }
    }

    size_t getStackSize() const {
        return std::distance(callbacks.begin(), callbacks.end());
    }

protected:
    virtual void handle(T* handler, void* param) = 0;

private:
    std::deque<T*> callbacks;
};

}  // namespace handler

#endif