#include "constexpr_string.h"
#include <iostream>
using namespace std::string_view_literals;

int main() {
    static_assert(CSTR("hello, world").view() == "hello, world"sv);
    static_assert(CSTR("hello, world").substr<2, 4>().view() == "llo,"sv);
    static_assert(CSTR("hello, world").remove_prefix<5>().view() == ", world"sv);
    static_assert(CSTR("hello, world").remove_suffix<5>().view() == "hello, "sv);
    static_assert(CSTR("hello, world").reverse().view() == "dlrow ,olleh"sv);
    static_assert(join(CSTR("hello"), CSTR(", "), CSTR("world")).view() == "hello, world"sv);
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
