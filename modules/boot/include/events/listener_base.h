#ifndef TPGZ_BOOT_LISTENERS_BASE_H
#define TPGZ_BOOT_LISTENERS_BASE_H

#include <rels/include/cxx.h>
#include <rels/include/defines.h>
#include <cstddef>
#include <concepts>
#include <type_traits>
#include <boot/include/utils/containers/deque.h>
#include <algorithm>

namespace events {
/**
 * @brief C++20 Concept to constrain the types to executable functions.
 *
 * @tparam Callback Constraint to be a function.
 */
template <typename Callback>
concept Function = std::is_function_v<std::remove_pointer_t<Callback>>;

/**
 * @brief Listener class, made to produce listeners which can dispatch events to registered
 * functions.
 *
 * @tparam Callback The signature of the callback functions to register.
 */
template <Function Callback>
class ListenerBase {
public:
    ListenerBase() {}
    virtual ~ListenerBase() {}

    /**
     * @brief Registeres a listener to run at the listened event.
     *
     * @param listener Function to register.
     */
    void addListener(Callback* listener) { callbacks.push_back(listener); }

    /**
     * @brief Unregisters a function.
     *
     * @param listener Function to unregister
     * @return true The function was previously registered and has been removed.
     * @return false The function was not previously registered.
     */
    bool removeListener(Callback* listener) {
        for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
            if (*it == listener) {
                callbacks.erase(it);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Calls all the registered functions with the given arguments.
     *
     * @tparam Args
     * @param args
     */
    template <typename... Args>
    void dispatchAll(Args... args) requires std::invocable<Callback, Args...> {
        for (Callback* cb : callbacks) {
            cb(args...);
        }
    }

    size_t getCount() const { return std::distance(callbacks.begin(), callbacks.end()); }

private:
    tpgz::containers::deque<std::remove_pointer_t<Callback>*> callbacks;
};

}  // namespace events

#endif