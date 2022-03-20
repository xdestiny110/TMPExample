#include "constexpr_string.h"
#include <iostream>
using namespace std::string_view_literals;

int main() {
    static_assert(CSTR("123").view() == "123"sv);
    static_assert(CSTR("123").substr<1, 2>().view() == "23"sv);
    static_assert(CSTR("hello, world!").reverse().view() == "!dlrow ,olleh"sv);
    static_assert(join(CSTR("123"), CSTR("123"), CSTR("abc")).view() == "123123abc"sv);
    static_assert(CSTR("hello, world").find(CSTR("llo")) == 2);
    static_assert(CSTR("hello, world").find("llo"sv) == 2);
    static_assert(CSTR("hello, world").find_first_not_of(CSTR("hello")) == 5);
    static_assert(CSTR("hello, world").find_first_not_of("hello"sv) == 5);
    static_assert(CSTR("hello, world").find_last_of(CSTR("wor")) == 9);
    static_assert(CSTR("hello, world").find_last_of("wor"sv) == 9);
    static_assert(CSTR("hello, world").find_last_not_of(CSTR("rld")) == 8);
    static_assert(CSTR("hello, world").find_last_not_of("rld"sv) == 8);

    return 0;
}
