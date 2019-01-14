#include "nonstd/value_ptr.hpp"

using nonstd::value_ptr;

int main()
{
    value_ptr<int> vp;

    int x = vp.value();  // asserts (normally throws)
}

// cl -nologo -I../include 03-no-exceptions.cpp && 03-no-exceptions
// g++ -Wall -fno-exceptions -I../include -o 03-no-exceptions 03-no-exceptions.cpp && 03-no-exceptions
