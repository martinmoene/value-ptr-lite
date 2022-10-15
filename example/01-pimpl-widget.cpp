#include "01-pimpl-widget.hpp"

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

Widget::~Widget() {}

Widget::Widget( int x )
: ptr( Widget::Pimpl( x ) )     // or: ptr( x )
{}

int Widget::next()
{
    return ptr->next();
}

