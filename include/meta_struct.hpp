#pragma once

#include <fixed_string.hpp>

#include <utility>

namespace meta {

    template <fixed_string Tag, typename T>
    struct tagged_value {
        T value;
    };

    template <fixed_string Tag>
    struct arg_type {
        template <typename T>
        constexpr auto operator=(T t) const {
            return tagged_value<Tag, T>{std::move(t)};
        }
    };

    template <fixed_string Tag>
    inline constexpr auto arg = arg_type<Tag>{};

    template <typename... TagValues>
    struct params : TagValues... {};

    template <typename... Members>
    struct meta_struct_impl : Members... {
        template <typename Params>
        constexpr meta_struct_impl(Params p) 
            : Members(std::move(p))... { }
    };

    template <fixed_string Tag, typename T>
    struct member {
        static constexpr auto tag() { return Tag; }
        using value_type = T;

        template <typename Type>
        constexpr member(tagged_value<Tag, Type> tv) 
            : value(std::move(tv.value)) {}

        T value;
    };

    template <typename... Members>
    struct meta_struct : meta_struct_impl<Members...> {
        using base_type = meta_struct_impl<Members...>;
        template <typename... TagValues>
        meta_struct(TagValues... tag_values) 
            : base_type(params(std::move(tag_values)...)) {}
    };

    template <fixed_string Tag, typename T>
    decltype(auto) get_impl(member<Tag, T>& m) {
        return (m.value);
    }

    template <fixed_string Tag, typename MetaStruct>
    decltype(auto) get(MetaStruct&& s) {
        return get_impl<Tag>(std::forward<MetaStruct>(s));
    }

} // namespace meta