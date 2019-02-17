#include "01-pimpl-widget.hpp"

int main()
{
    Widget w1( 42 );
//  Widget w2( w1 );

    assert( w1.next() == 43 );
//  assert( w2.next() == 43 );
}

// cl  -EHsc -I../include 01-pimpl.cpp 01-pimpl-widget.cpp && 01-pimpl.exe
// g++ -std=c++11 -I../include -o 01-pimpl.exe 01-pimpl-widget.cpp 01-pimpl.cpp && 01-pimpl.exe
