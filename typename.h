#pragma once
#include "constexpr_string.h"

namespace {
template <typename T>
constexpr auto raw_type_name_impl() noexcept {
#if defined(__clang__)
    return std::string_view{__PRETTY_FUNCTION__};
#elif defined(__GNUC__)
    return std::string_view{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
    return std::string_view{__FUNCSIG__};
#else
    static_assert(false);
#endif
}

template <typename T>
constexpr auto raw_type_name() noexcept {
#if defined(__clang__)

#elif defined(__GNUC__)

#elif defined(_MSC_VER)
    return CSTR(raw_type_name_impl<T>()).remove_suffix<16>().remove_prefix<55>();
#else
    static_assert(false);
#endif
}
} // namespace

template <typename T>
constexpr auto type_name() noexcept {
    return raw_type_name<T>();
}
