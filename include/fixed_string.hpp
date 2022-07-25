#pragma once

#include <cstddef>
#include <algorithm>

namespace meta {
    template <std::size_t N>
    struct fixed_string {
        constexpr fixed_string(const char(&str)[N + 1]) {
            std::copy_n(str, N + 1, data);
        }
        auto operator <=>(const fixed_string&) const = default;
        char data[N + 1] = {};
    };

    template <std::size_t N>
    fixed_string(const char(&)[N])->fixed_string<N - 1>;
} // namespace meta