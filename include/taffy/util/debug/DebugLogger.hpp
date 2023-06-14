#pragma once

#include <mutex>   // for: std::mutext, std::lock_guard<T>
#include <deque>   // for: std::deque<T>
#include <string>  // for: std::string
#include <sstream> // for: std::ostringstream
#include <cstdio>  // for: printf()

#include <taffy/tree/node/NodeId.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/* RUST
    static EMPTY_STRING: String = String::new();
*/
// TODO: it's must be NOT in global scope, since it pollute namespace, if
// that file included, but 'feature debug' not enabled & global 'NODE_LOGGER'
// not constructed.
static const std::string EMPTY_STRING = std::string{};

/* RUST
    #[doc(hidden)]
    pub struct DebugLogger {
        stack: Mutex<Vec<String>>,
*/

class DebugLogger
{
    std::mutex mutex;

    // Notice, that instead of std::vector<std::string> here is used
    // std::deque<std::string> - since we dont actually need to store strings 
    // continuosly in memory.
    // 
    // std::stack<std::string> (which is basically std::list<std::string>) not
    // suitable here, since we need to access 'last' element, so instead of 
    // linked-list we use doubly-linked-list.
    std::deque<std::string> stack; 

public:

    /* RUST
        pub const fn new() -> Self 
    */
    static DebugLogger New()
    {
        return {};
    }
    DebugLogger() = default;

    /* RUST
        pub fn push_node(&self, new_key: NodeId) 
    */
    void push_node(NodeId new_key)
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        std::string key_string = Debug(new_key);
        this->stack.push_back(std::move(key_string));
    }

    /* RUST
        pub fn pop_node(&self)
    */
    void pop_node()
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->stack.pop_back();
    }

    /* RUST
        pub fn log(&self, message: impl Display)
    */
    template <typename T>
    // TODO: add 'Display' check here - is operator << with ostream exists
    void log(const T& message)
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        const std::string& key =
            !this->stack.empty() ? this->stack.back() : EMPTY_STRING;
        const size_t level = this->stack.size() * 4;

        const std::string message_str = (std::ostringstream{} << message).str();

        printf(
            "%s%s: %s\n",
            std::string(level, ' ').c_str(),
            key.c_str(),
            message_str.c_str()
        );
    }

    /* RUST
        pub fn labelled_log(&self, label: &str, message: impl Display)
    */
    template <typename T>
    // TODO: add 'Display' check here - is operator << with ostream exists
    void labelled_log(const char* label, const T& message)
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        const std::string& key =
            !this->stack.empty() ? this->stack.back() : EMPTY_STRING;
        const size_t level = this->stack.size() * 4;

        const std::string message_str = (std::ostringstream{} << message).str();

        printf(
            "%s%s: %s %s\n",
            std::string(level, ' ').c_str(),
            key.c_str(),
            label,
            message_str.c_str()
        );
    }

    /* RUST
        pub fn debug_log(&self, message: impl Debug)
    */
    template <typename T,
              typename = typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    void debug_log(const T& message)
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        const std::string& key =
            !this->stack.empty() ? this->stack.back() : EMPTY_STRING;
        const size_t level = this->stack.size() * 4;
        printf(
            "%s%s: %s\n",
            std::string(level, ' ').c_str(),
            key.c_str(),
            Debug(message).c_str()
        );
    }

    /* RUST
        pub fn labelled_debug_log(&self, label: &str, message: impl Debug)
    */
    template <typename T,
              typename = typename std::enable_if< utils::is_Debug<T>::value == true >::type>
    void labelled_debug_log(const char* label, const T& message)
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        const std::string& key =
            !this->stack.empty() ? this->stack.back() : EMPTY_STRING;
        const size_t level = this->stack.size() * 4;
        printf(
            "%s%s: %s %s\n",
            std::string(level, ' ').c_str(),
            key.c_str(),
            label,
            Debug(message).c_str()
        );
    }
};

/* RUST
    #[cfg(any(feature = "debug", feature = "profile"))]
    pub(crate) static NODE_LOGGER: DebugLogger = DebugLogger::new();
*/
#if defined(TAFFY_FEATURE_DEBUG) || defined(TAFFY_FEATURE_PROFILE)
    static DebugLogger NODE_LOGGER;
#endif // TAFFY_FEATURE_DEBUG || TAFFY_FEATURE_PROFILE

} // namespace taffy
