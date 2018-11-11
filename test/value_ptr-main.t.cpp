// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/value-ptr-lite
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "value_ptr-main.t.hpp"

#define nsvp_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define nsvp_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "value-ptr-lite version" "[.value-ptr][.version]" )
{
    nsvp_PRESENT( value_ptr_lite_MAJOR );
    nsvp_PRESENT( value_ptr_lite_MINOR );
    nsvp_PRESENT( value_ptr_lite_PATCH );
    nsvp_PRESENT( value_ptr_lite_VERSION );
}

CASE( "value-ptr configuration" "[.value-ptr][.config]" )
{
    nsvp_PRESENT( nsvp_CONFIG_COMPARE_POINTERS );
    nsvp_PRESENT( nsvp_CPLUSPLUS );
}

CASE( "C++ language: __cplusplus" "[.stdc++]" )
{
    nsvp_PRESENT( __cplusplus );
}

CASE( "C++ compiler: compiler version" "[.compiler]" )
{
    nsvp_PRESENT( nsvp_COMPILER_CLANG_VERSION );
    nsvp_PRESENT( nsvp_COMPILER_GNUC_VERSION );
    nsvp_PRESENT( nsvp_COMPILER_MSVC_VERSION );
}

CASE( "C++ language: presence of C++ language features" "[.stdlanguage]" )
{
    nsvp_PRESENT( nsvp_HAVE_CONSTEXPR_11 );
    nsvp_PRESENT( nsvp_HAVE_CONSTEXPR_14 );
    nsvp_PRESENT( nsvp_HAVE_INITIALIZER_LIST );
    nsvp_PRESENT( nsvp_HAVE_IS_DEFAULT );
    nsvp_PRESENT( nsvp_HAVE_NOEXCEPT );
    nsvp_PRESENT( nsvp_HAVE_NULLPTR );
    nsvp_PRESENT( nsvp_HAVE_REF_QUALIFIER );
}

CASE( "C++ library: presence of C++ library features" "[.stdlibrary]" )
{
    nsvp_PRESENT( nsvp_HAVE_TYPE_TRAITS );

    nsvp_PRESENT( nsvp_HAS_CPP0X );

#if defined _HAS_CPP0X
    nsvp_PRESENT( _HAS_CPP0X );
#else
    nsvp_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o value-ptr-lite.t.exe value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass

cl -EHsc -I../include/nonstd value-ptr-lite.t.cpp value_ptr.t.cpp && value-ptr-lite.t.exe --pass
#endif

// end of file
