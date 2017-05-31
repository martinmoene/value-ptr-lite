#include "value_ptr.hpp"

using namespace nonstd;

struct Widget
{
   Widget( int x );

#if nsvp_CPP11_OR_GREATER
   // Thanks to value_ptr we get value semantics for free
   Widget( Widget const& ) = default;
   Widget & operator=( Widget const& ) = default;
   ~Widget() = default;
#endif

   int next();

   struct Pimpl;
   value_ptr<Pimpl> ptr;
};

struct Widget::Pimpl
{
    int x;

    Pimpl( int v )
    : x( v ) {}

    int next()
    {
        return ++x;
    }
};

Widget::Widget( int x )
: ptr( Widget::Pimpl( x ) )     // or: ptr( x )
{}

int Widget::next()
{
    return ptr->next();
}

int main()
{
    Widget w1( 42 );
    Widget w2( w1 );

    assert( w1.next() == 43 );
    assert( w2.next() == 43 );
}

// cl  -EHsc -I../include/nonstd/ 01-pimpl.cpp && 01-pimpl.exe
// g++ -std=c++11 -I../include/nonstd/ -o 01-pimpl.exe 01-pimpl.cpp && 01-pimpl.exe
