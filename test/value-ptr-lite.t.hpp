// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/value-ptr-lite
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef value_ptr_lite_T_INCLUDED
#define value_ptr_lite_T_INCLUDED

#include "value_ptr.hpp"
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

template< typename T, class Cloner, class Deleter>
inline std::ostream & operator<<( std::ostream & os, ::nonstd::value_ptr<T, Cloner, Deleter> const & vp )
{
    os << "[value_ptr: "; if (vp) os << *vp; else os << "[empty]"; return os << "]";
}

}

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // value_ptr_lite_T_INCLUDED

// end of file
