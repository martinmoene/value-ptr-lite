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

CASE( "value-ptr-lite version" "[.version]" )
{
    nsvp_PRESENT( value_ptr_lite_VERSION );
}

CASE( "C++ compiler: compiler version" "[.compiler]" )
{
#if nsvp_COMPILER_CLANG_VERSION
    nsvp_PRESENT( nsvp_COMPILER_CLANG_VERSION );
#else
    nsvp_ABSENT(  nsvp_COMPILER_CLANG_VERSION );
#endif

#if nsvp_COMPILER_GNUC_VERSION
    nsvp_PRESENT( nsvp_COMPILER_GNUC_VERSION );
#else
    nsvp_ABSENT(  nsvp_COMPILER_GNUC_VERSION );
#endif

#if nsvp_COMPILER_MSVC_VERSION
    nsvp_PRESENT( nsvp_COMPILER_MSVC_VERSION );
#else
    nsvp_ABSENT(  nsvp_COMPILER_MSVC_VERSION );
#endif
}

CASE( "C++ language: __cplusplus" "[.stdc++]" )
{
    nsvp_PRESENT( __cplusplus );
}

CASE( "C++ language: nsvp_CPP11_OR_GREATER" "[.stdc++]" )
{
#if nsvp_CPP11_OR_GREATER
    nsvp_PRESENT( nsvp_CPP11_OR_GREATER );
#else
    nsvp_ABSENT(  nsvp_CPP11_OR_GREATER );
#endif
}

CASE( "C++ language: nsvp_CPP14_OR_GREATER" "[.stdc++]" )
{
#if nsvp_CPP14_OR_GREATER
    nsvp_PRESENT( nsvp_CPP14_OR_GREATER );
#else
    nsvp_ABSENT(  nsvp_CPP14_OR_GREATER );
#endif
}

CASE( "C++ language: nsvp_CPP17_OR_GREATER" "[.stdc++]" )
{
#if nsvp_CPP17_OR_GREATER
    nsvp_PRESENT( nsvp_CPP17_OR_GREATER );
#else
    nsvp_ABSENT(  nsvp_CPP17_OR_GREATER );
#endif
}

CASE( "C++ language: presence of C++ language features" "[.stdlanguage]" )
{
#if nsvp_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    nsvp_PRESENT( nsvp_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else
    nsvp_ABSENT(  nsvp_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if nsvp_HAVE_CONSTEXPR_11
    nsvp_PRESENT( nsvp_HAVE_CONSTEXPR_11 );
#else
    nsvp_ABSENT(  nsvp_HAVE_CONSTEXPR_11 );
#endif

#if nsvp_HAVE_CONSTEXPR_14
    nsvp_PRESENT( nsvp_HAVE_CONSTEXPR_14 );
#else
    nsvp_ABSENT(  nsvp_HAVE_CONSTEXPR_14 );
#endif

#if nsvp_HAVE_ENUM_CLASS
    nsvp_PRESENT( nsvp_HAVE_ENUM_CLASS );
#else
    nsvp_ABSENT(  nsvp_HAVE_ENUM_CLASS );
#endif

#if nsvp_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    nsvp_PRESENT( nsvp_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else
    nsvp_ABSENT(  nsvp_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if nsvp_HAVE_EXPLICIT_CONVERSION
    nsvp_PRESENT( nsvp_HAVE_EXPLICIT_CONVERSION );
#else
    nsvp_ABSENT(  nsvp_HAVE_EXPLICIT_CONVERSION );
#endif

#if nsvp_HAVE_IS_DEFAULT
    nsvp_PRESENT( nsvp_HAVE_IS_DEFAULT );
#else
    nsvp_ABSENT(  nsvp_HAVE_IS_DEFAULT );
#endif

#if nsvp_HAVE_NOEXCEPT
    nsvp_PRESENT( nsvp_HAVE_NOEXCEPT );
#else
    nsvp_ABSENT(  nsvp_HAVE_NOEXCEPT );
#endif

#if nsvp_HAVE_NULLPTR
    nsvp_PRESENT( nsvp_HAVE_NULLPTR );
#else
    nsvp_ABSENT(  nsvp_HAVE_NULLPTR );
#endif

#if nsvp_HAVE_REF_QUALIFIER
    nsvp_PRESENT( nsvp_HAVE_REF_QUALIFIER );
#else
    nsvp_ABSENT(  nsvp_HAVE_REF_QUALIFIER );
#endif
}

CASE( "C++ library: presence of C++ library features" "[.stdlibrary]" )
{
#if nsvp_HAVE_TYPE_TRAITS
    nsvp_PRESENT( nsvp_HAVE_TYPE_TRAITS );
#else
    nsvp_ABSENT(  nsvp_HAVE_TYPE_TRAITS );
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
