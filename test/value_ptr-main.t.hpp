// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/value-ptr-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef value_ptr_lite_T_INCLUDED
#define value_ptr_lite_T_INCLUDED

#include "nonstd/value_ptr.hpp"

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include <iostream>

namespace nonstd { namespace vptr {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

template< typename T, class Cloner, class Deleter>
inline std::ostream & operator<<( std::ostream & os, ::nonstd::value_ptr<T, Cloner, Deleter> const & vp )
{
    os << "[value_ptr: "; if (vp) os << *vp; else os << "[empty]"; return os << "]";
}

}}

namespace lest {

using ::nonstd::vptr::operator<<;

} // namespace lest

#include "lest_cpp03.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // value_ptr_lite_T_INCLUDED

// end of file
