#include "typename.h"
#include <iostream>
using namespace std::string_view_literals;

int main() {
    static_assert(type_name<float>().view() == "float"sv);
    static_assert(type_name<unsigned char>().view() == "unsigned char"sv);
    static_assert(type_name<const double&>().view() == "const double&"sv);
}