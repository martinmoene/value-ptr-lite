#include <utility>
#include <iostream>
#include <nonstd/value_ptr.hpp>
#include <nonstd/variant.hpp>

struct TestStruct
{
    int a;
};

int main()
{
    nonstd::value_ptr<TestStruct> tmp(TestStruct{10});
    // std::variant<int, char> var;
    nonstd::variant<int, char> var2;

    std::cout << 
        tmp->a       << " " << 
//      var.index()  << " " << 
        var2.index() << 
        std::endl;

    return 0;
}

// cl -std:c++17 -Dvariant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD -nologo -EHsc -I../../any-lite/include -I../../optional-lite/include -I../../value-ptr-lite/include -I../../variant-lite/include 04-vp-variant.cpp && 04-vp-variant
// g++ -std=c++17 -Wall -I../../any-lite/include -I../../optional-lite/include -I../../value-ptr-lite/include -I../../variant-lite/include -o 04-vp-variant 04-vp-variant.cpp && 04-vp-variant
