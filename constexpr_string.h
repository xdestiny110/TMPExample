#pragma once
#include <cstdlib>
#include <string_view>

#define CSTR(s)                                                                                                        \
    ([] {                                                                                                              \
        struct tmp {                                                                                                   \
            static constexpr auto get() { return std::string_view{s}; }                                                \
        };                                                                                                             \
        return CSTRHelper(tmp{});                                                                                      \
    }())

namespace {
template <typename T, std::size_t... N>
constexpr auto CSTRImpl(std::index_sequence<N...>) {
    return constexpr_string<T::get()[N]...>{};
}

template <typename T>
constexpr auto CSTRHelper(T) {
    return CSTRImpl<T>(std::make_index_sequence<T::get().size()>{});
}

template <std::size_t... Is>
constexpr auto indexSequenceReverse(std::index_sequence<Is...>)
    -> decltype(std::index_sequence<sizeof...(Is) - 1U - Is...>{});

template <std::size_t N>
using makeIndexSequenceReverse
   = decltype(indexSequenceReverse(std::make_index_sequence<N>{}));

} // namespace

template <char... chars>
struct constexpr_string {
    static constexpr std::size_t npos = -1;
    static constexpr std::size_t size() noexcept { return sizeof...(chars); }
    static constexpr std::string_view view(std::size_t pos = 0, std::size_t cnt = sizeof...(chars)) noexcept {
        return std::string_view(m_data + pos, cnt);
    }

    template <std::size_t N0, std::size_t N1>
    static constexpr auto substr() noexcept {
        struct tmp {
            static constexpr auto get() { return std::string_view{m_data + N0, N1}; }
        };
        return CSTRHelper(tmp{});
    }

    static constexpr auto reverse() noexcept {
        struct tmp {
            static constexpr auto get() { return std::string_view{m_data}; }
        };
        return CSTRImpl<tmp>(makeIndexSequenceReverse<sizeof...(chars)>{});
    }

    template <typename T>
    static constexpr std::size_t find(T) noexcept {
        return view().find(T::view());
    }

    template<>
    static constexpr std::size_t find<std::string_view>(std::string_view sv) noexcept {
        return view().find(sv);
    }

    template <typename T>
    static constexpr std::size_t find_first_not_of(T) noexcept {
        return view().find_first_not_of(T::view());
    }

    template<>
    static constexpr std::size_t find_first_not_of<std::string_view>(std::string_view sv) noexcept {
        return view().find_first_not_of(sv);
    }

    template <typename T>
    static constexpr std::size_t find_last_of(T) noexcept {
        return view().find_last_of(T::view());
    }

    template<>
    static constexpr std::size_t find_last_of<std::string_view>(std::string_view sv) noexcept {
        return view().find_last_of(sv);
    }

    template <typename T>
    static constexpr std::size_t find_last_not_of(T) noexcept {
        return view().find_last_not_of(T::view());
    }

    template<>
    static constexpr std::size_t find_last_not_of<std::string_view>(std::string_view sv) noexcept {
        return view().find_last_not_of(sv);
    }

private:
    static constexpr char m_data[]{chars..., 0};
};

namespace {
template <typename T, typename U>
struct join_helper;

template <char... c0, char... c1>
struct join_helper<constexpr_string<c0...>, constexpr_string<c1...>> {
    using type = constexpr_string<c0..., c1...>;
};

template <typename T, typename U>
using join_helper_t = typename join_helper<T, U>::type;

template <typename... Ts>
struct join_seq_helper;

template <typename T>
struct join_seq_helper<T> {
    using type = T;
};

template <typename... Ts>
using join_seq_helper_t = typename join_seq_helper<Ts...>::type;

template <typename T, typename... Us>
struct join_seq_helper<T, Us...> {
    using type = join_helper_t<T, join_seq_helper_t<Us...>>;
};

} // namespace

template <typename... Ts>
constexpr auto join(Ts...) {
    return join_seq_helper_t<Ts...>{};
}
