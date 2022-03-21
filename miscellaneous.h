#pragma once
#include <type_traits>

template<typename T, typename U, typename... Us>
struct is_one_of {
    static constexpr bool value = std::is_same_v<T, U> || is_one_of<T, Us...>::value;
};

template<typename T, typename U, typename... Us>
constexpr bool is_one_of_v = is_one_of<T, U, Us...>::value;

template<typename T, typename U>
struct is_one_of<T, U> {
    static constexpr bool value = std::is_same_v<T, U>;
};

template<typename T, template<typename...> typename U>
struct is_instantiation_of : std::false_type {};

template<template<typename...> typename T, typename... Ts>
struct is_instantiation_of<T<Ts...>, T> : std::true_type {};

template<typename T, template<typename...> typename U>
constexpr bool is_instantiation_of_v = is_instantiation_of<T, U>::value;

template<typename T, typename = void>
struct has_member : std::false_type {};

template<typename T>
struct has_member<T, std::void_t<decltype(T::member)>> : std::true_type {};

template<typename T>
constexpr bool has_member_v = has_member<T>::value;

template<typename T, typename = void>
struct has_func : std::false_type {};

template<typename T>
struct has_func<T, std::void_t<decltype(std::declval<T>().func())>> : std::true_type {};

template<typename T>
constexpr bool has_func_v = has_func<T>::value;
