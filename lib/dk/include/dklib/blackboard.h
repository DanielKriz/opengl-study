#ifndef DK_BLACKBOARD_H
#define DK_BLACKBOARD_H

#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <variant>

#include <dklib/util.h>

namespace dk {

template <typename T>
concept Printable = requires(const std::ostream &os, const T &tvalue) { os << tvalue; };

// TODO: This class could be a template which would require the user to specify
// types in a variatic template, it would be pracically a drop in replacement
// which would support any type.

template <typename... Ts>
class BlackBoard {
public:
    using value_type = std::variant<Ts...>;

    template <typename T>
    [[nodiscard]] constexpr std::optional<const T>
    get(const std::string &key) const noexcept {
        if (auto it = items_.find(key); it != items_.end()) {
            const std::lock_guard lock { mutex_ };
            return std::get<T>((*it).second);
        }
        return {};
    };

    // TODO: this is good for trivially constructible types, but bad for others
    // I should create an overload for different types, which would then
    // invoke copy ctor
    template <typename T>
    void set(const std::string &key, T value) noexcept {
        const std::lock_guard lock { mutex_ };
        items_.insert_or_assign(key, value);
    };

    template <typename T, typename... Args>
    void emplace(const std::string &key, Args &&...args) noexcept {
        const std::lock_guard lock { mutex_ };
        items_.emplace(key, std::forward<Args>(args)...);
    };

    template <typename... Us>
    friend std::ostream &operator<<(std::ostream &os, const BlackBoard<Us...> &board);

private:
    std::map<std::string, value_type> items_;
    mutable std::mutex mutex_;
};

template <typename... Ts>
BlackBoard() -> BlackBoard<int, std::size_t, float, double, std::string>;

template <typename... Ts>
inline std::ostream &operator<<(std::ostream &os, const BlackBoard<Ts...> &board) {
    // TODO: if you would surround the key value with "value" then it would
    // be valid JSON
    os << "{";
    bool is_first = true;
    for (const auto &[k, v] : board.items_) {
        if (is_first) {
            is_first = false;
        } else {
            os << ',' << ' ';
        }
        std::visit(
            util::overload {
                [&os, &k](float x) { os << k << ": " << std::fixed << x; },
                [&os, &k](double x) { os << k << ": " << std::fixed << x; },
                [&os, &k](std::string x) { os << k << ": " << '"' << x << '"'; },
                [&os, &k](auto x) { os << k << ": " << x; },
            },
            v
        );
    }
    os << "}";
    return os;
}
} // namespace dk

#endif // DK_BLACKBOARD_H
