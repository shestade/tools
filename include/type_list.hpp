#pragma once

#include <utility>
#include <type_traits>

namespace meta {

    template <typename... Ts>
    struct tl;

    template <typename TL>
    struct head_impl;

    template<typename T, typename... Ts>
    struct head_impl<tl<T, Ts...>> {
        using type = T;
    };

    template<typename TL>
    using head_t = typename head_impl<TL>::type;

    template <typename T, typename TL>
    struct push_head_impl;

    template<typename T, typename... Ts>
    struct push_head_impl<T, tl<Ts...>> {
        using type = tl<T, Ts...>;
    };

    template<typename T, typename TL>
    using push_head_t = typename push_head_impl<T, TL>::type;

    template <typename TL>
    struct tail_impl;

    template<typename T, typename... Ts>
    struct tail_impl<tl<T, Ts...>> {
        using type = tl<Ts...>;
    };

    template<typename T>
    using tail_t = typename tail_impl<T>::type;

    template <typename TL, typename T>
    struct push_back_impl;

    template<typename... Ts, typename T>
    struct push_back_impl<tl<Ts...>, T> {
        using type = tl<Ts..., T>;
    };

    template<typename T, typename TL>
    using push_back_t = typename push_back_impl<T, TL>::type;

    template <typename TL>
    struct empty_impl : std::false_type {};

    template <>
    struct empty_impl<tl<>> : std::true_type {};

    template <typename TL>
    constexpr bool empty_v = empty_impl<TL>::value;

    template <typename TL, bool Empty = empty_v<TL>>
    struct reverse_impl;

    template <typename TL>
    using reverse_t = typename reverse_impl<TL>::type;

    template <typename TL>
    struct reverse_impl<TL, true> {
        using type = TL;
    };

    template <typename TL>
    struct reverse_impl<TL, false> 
        : push_back_impl<typename reverse_t<tail_t<TL>>, head_t<TL>> {};

    template <typename TL, typename F>
    struct transform_impl;

    template <typename... Ts, typename F>
    struct transform_impl<tl<Ts...>, F> {
        using type = tl<typename F::template apply<Ts>...>;
    };

    template <typename T, typename F>
    using transform_t = typename transform_impl<T, F>::type;

    template <typename... TLs>
    struct concat_impl;

    template <typename... Ts1, typename... Ts2>
    struct concat_impl<tl<Ts1...>, tl<Ts2...>> {
        using type = tl<Ts1..., Ts2...>;
    };

    template <typename... TLs>
    using concat_t = typename concat_impl<TLs...>::type;

    template <template <typename> typename F, typename TL>
    struct filter_impl;

    template <template <typename> typename F, typename TL>
    using filter_t = typename filter_impl<F, TL>::type;

    template <template <typename> typename F>
    struct filter_impl<F, tl<>> {
        using type = tl<>;
    };

    template <template <typename> typename F, typename T, typename... Ts>
    struct filter_impl<F, tl<T, Ts...>> 
        : std::conditional<F<T>::value,
            concat_t<tl<T>, typename filter_impl<F, tl<Ts...>>::type>,
            filter_t<F, tl<Ts...>>> {};


} // namespace meta