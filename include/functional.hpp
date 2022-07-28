#pragma once

namespace func {

    constexpr auto compose = [](auto&& fn) constexpr {
        return[fn = std::forward<decltype(fn)>(fn)](auto&& redex) constexpr {
            return[&](auto in) constexpr {
                return redex(fn(in));
            };
        };
    };

    constexpr auto identity = [](auto x) constexpr { return x; };

} // namespace func