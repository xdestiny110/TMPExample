#include "miscellaneous.h"
#include <vector>

struct generic {};

struct test {
    void func() {}
    int member;
};

int main() {
    static_assert(is_one_of_v<int, float, uint32_t, int32_t>);
    std::vector<int> v;
    static_assert(is_instantiation_of_v<decltype(v), std::vector>);
    static_assert(has_member_v<test>);
    static_assert(!has_member_v<generic>);
    static_assert(has_func_v<test>);
    static_assert(!has_func_v<generic>);
    return 0;
}