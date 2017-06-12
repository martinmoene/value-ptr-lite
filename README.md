# value-ptr lite
A C++ smart-pointer with value semantics for C++98, C++11 and later

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-98-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-14-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/martinmoene/value-ptr-lite.svg?branch=master)](https://travis-ci.org/martinmoene/value-ptr-lite) [![Build status](https://ci.appveyor.com/api/projects/status/w2dgn3fxyrd6vcq8?svg=true)](https://ci.appveyor.com/project/martinmoene/value-ptr-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fvalue-ptr-lite.svg)](https://github.com/martinmoene/value-ptr-lite/releases) [![download](https://img.shields.io/badge/latest%20version%20%20-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/value-ptr-lite/master/include/nonstd/value_ptr.hpp)


**Contents**
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other value_ptr implementations](#other-value-ptr-implementations)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Pimpl example usage
-------------------

```Cpp
// in header file:

#include "value_ptr.hpp"

// Thanks to value_ptr we get value semantics for free:

struct Widget
{
   Widget( int x );

   int next();

   struct Pimpl;
   nonstd::value_ptr<Pimpl> ptr;
};

// in source file:

struct Widget::Pimpl
{
    int x;

    Pimpl( int v ) : x( v ) {}

    int next() { return ++x; }
};


Widget::Widget( int x ) : ptr( Widget::Pimpl( x ) ) {}  // or: ptr( x )

int Widget::next() { return ptr->next(); }

int main()
{
    Widget w1( 42 );
    Widget w2( w1 );

    assert( w1.next() == 43 );
    assert( w2.next() == 43 );
}
```

In a nutshell
-------------
**value-ptr lite** is a single-file header-only library to bring value semantics to heap resources. In certain situations, such as with the pimpl idiom in the example above, a pointer must be used while value semantics would be prefered. This is where `value_ptr` comes into play. A `value_ptr` is similar to a `std::optional` in many respects and one could say a `value_ptr` is more value than pointer.  

**Features and properties of value-ptr lite** are ease of installation (single header), freedom of dependencies other than the standard library.

**Limitations of value-ptr lite** are ... .


License
-------
*value-ptr lite* uses the [MIT](LICENSE) license.


Dependencies
------------
*value-ptr lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*value-ptr lite* is a single-file header-only library. Put `value_ptr.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


Synopsis
--------

**Contents**
- [Types in namespace nonstd](#types-in-namespace-nonstd)
- [Interface of *value-ptr lite*](#interface-of-value-ptr-lite)
- [Non-member functions for *value-ptr lite*](#non-member-functions-for-value-ptr-lite)
- [Configuration macros](#configuration-macros)

### Types in namespace nonstd

| Purpose               | Type | Notes |
|-----------------------|------|-------|
| Smart pointer with<br>value semantics | class value_ptr  | &nbsp; |
| In-place construction | struct in_place_tag              | &nbsp; |
| &nbsp;                | in_place                         | select type or index for in-place construction |
| &nbsp;                | nonstd_lite_in_place_type_t( T)  | macro for alias template in_place_type_t&lt;T>  |
| &nbsp;                | nonstd_lite_in_place_index_t( T )| macro for alias template in_place_index_t&lt;T> |

### Interface of *value-ptr lite*

#### Class `value_ptr`

| Kind |[[1]](#ref1)| Type / Method | Note / Result |
|-------|:------:|-----------------------------|---------------|
| Value types    |&#10003;| element_type           |&nbsp; |
| &nbsp;         |&#10003;| pointer                |&nbsp; |
| &nbsp;         |&#10003;| reference              |&nbsp; |
| &nbsp;         |&#10003;| const_pointer          |&nbsp; |
| &nbsp;         |&#10003;| const_reference        |&nbsp; |
| Lifetime types |&#10003;| cloner_type            |&nbsp; |
| &nbsp;         |&#10003;| deleter_type           |&nbsp; |
| Construction   |&nbsp;  |&nbsp;| &nbsp;|
| &nbsp;         |&#10003;| ...  | ...   |

### Non-member functions for *value-ptr lite*

| Kind                 |[[1]](#ref1)| std  | Function |
|--------------------------|:------:|:----:|----------|
| Relational operators     |&nbsp;  |&nbsp;| &nbsp;   |
| &nbsp;                   |&#10003;| ..   | ...      |
| Swap                     |&nbsp;  |&nbsp;| template< class T, class C, class D ><br>void swap( value_ptr&lt;T,C,D> & x, value_ptr&lt;T,C,D> & y ) noexcept(...) |
| Create                   |&nbsp;  |<C++11| template< class T, class C, class D ><br>value_ptr&lt;T,C,D> make_value( T const & v )      |
| &nbsp;                   |&nbsp;  | C++11| template< class T ><br>value_ptr< typename std::decay&lt;T>::type > make_value( T && v ) |
| &nbsp;                   |&nbsp;  | C++11| template< class T, class...Args ><br>value_ptr&lt;T,C,D> make_value( Args&&... args ) |
| &nbsp;                   |&nbsp;  | C++11| template< class T, class U, class... Args ><br>value_ptr&lt;T,C,D> make_value( std::initializer_list&lt;U> il, Args&&... args ) |
| Hash                     |&nbsp;  | C++11| template< class T ><br>class hash< nonstd::value_ptr&lt;T,C,D> > |


### Configuration macros

-D<b>nsvp_CONFIG_COMPARE_POINTERS</b>=0  
Define this to 1 to compare `value_ptr`'s pointer instead of the content it's pointing to. Default is 0.


Reported to work with
---------------------


Building the tests
------------------

### Buck

To run the tests:
```
prompt> buck run test/
```

### CMake

The following steps assume that the [value-ptr lite source code](https://github.com/martinmoene/value-ptr-lite) has been cloned into a directory named `c:\value-ptr-lite`.

1. Create a directory for the build outputs for a particular architecture.
Here we use c:\value-ptr-lite\build-win-x86-vc10.

        cd c:\value-ptr-lite
        md build-win-x86-vc10
        cd build-win-x86-vc10

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Visual Studio 10 2010" [see 3. below] ..

3. Optional. You can control above configuration through the following options:

   - `-DRING_SPAN_LITE_COLOURISE_TEST=ON`: use colour for pass, fail, default off

4. Build the test suite in the Debug configuration (alternatively use Release).

        cmake --build . --config Debug

5. Run the test suite.

        ctest -V -C Debug

All tests should pass, indicating your platform is supported and you are ready to use *value-ptr lite*. See the table with [supported types and functions](#features).


Other value-ptr implementations
-------------------------------
(TBD)


Notes and references
--------------------

<a id="ref1"></a>[1] Gaetano Checinski. [value_ptr — The Missing C++ Smart-pointer](https://hackernoon.com/value-ptr-the-missing-c-smart-pointer-1f515664153e) ([GitHub](https://github.com/LoopPerfect/valuable)). May 2017.  
<a id="ref2"></a>[2] Andrey Upadyshev. [PIMPL, Rule of Zero and Scott Meyers](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html) ([GitHub](https://github.com/oliora/samples/blob/master/spimpl.h)). December 29, 2015.  

Appendix
--------

**Contents**
- [A.1 Value-ptr  lite test specification](#a1-value-ptr-lite-test-specification)
- [A.2 Hidden test cases tagged with \[.applet\]](#a2-hidden-test-cases-tagged-with-applet)
- [A.3 Hidden test cases for compile-time information](#a3-hidden-test-cases-for-compile-time-information)

### A.1 value-ptr lite test specification

```
value_ptr: Allows to default construct an empty value_ptr
value_ptr: Allows to explicitly construct a disengaged, empty value_ptr via nullptr
value_ptr: Allows to default construct an empty value_ptr with a non-default-constructible
value_ptr: Allows to copy-construct from empty value_ptr
value_ptr: Allows to copy-construct from non-empty value_ptr
value_ptr: Allows to move-construct from value_ptr (C++11)
value_ptr: Allows to copy-construct from literal value
value_ptr: Allows to copy-construct from value
value_ptr: Allows to move-construct from value (C++11)
value_ptr: Allows to in-place construct from literal value (C++11)
value_ptr: Allows to in-place copy-construct from value (C++11)
value_ptr: Allows to in-place move-construct from value (C++11)
value_ptr: Allows to in-place copy-construct from initializer-list (C++11)
value_ptr: Allows to in-place move-construct from initializer-list (C++11)
value_ptr: Allows to construct from pointer to value
value_ptr: Allows to assign nullptr to disengage (C++11)
value_ptr: Allows to copy-assign from/to engaged and disengaged value_ptr-s
value_ptr: Allows to move-assign from/to engaged and disengaged value_ptr-s (C++11)
value_ptr: Allows to copy-assign from literal value
value_ptr: Allows to copy-assign from value
value_ptr: Allows to move-assign from value (C++11)
value_ptr: Allows to copy-emplace content from arguments (C++11)
value_ptr: Allows to move-emplace content from arguments (C++11)
value_ptr: Allows to copy-emplace content from intializer-list and arguments (C++11)
value_ptr: Allows to move-emplace content from intializer-list and arguments (C++11)
value_ptr: Allows to construct and destroy via user-specified cloner and deleter
value_ptr: Allows to construct via user-specified cloner with member data
value_ptr: Allows to obtain pointer to value via operator->()
value_ptr: Allows to obtain value via operator*()
value_ptr: Allows to obtain moved-value via operator*()
value_ptr: Allows to obtain engaged state via operator bool()
value_ptr: Allows to release its content
value_ptr: Allows to clear its content (reset)
value_ptr: Allows to replace its content (reset)
value_ptr: Allows to swap with other value_ptr (member)
value_ptr: Allows to swap with other value_ptr (non-member)
value_ptr: Provides relational operators (non-member, value_ptr pointer comparison: nsvp_CONFIG_COMPARE_POINTERS!=0)
value_ptr: Provides relational operators (non-member, value_ptr value comparison: nsvp_CONFIG_COMPARE_POINTERS==0)
value_ptr: Provides relational operators (non-member, value_ptr-value value comparison: nsvp_CONFIG_COMPARE_POINTERS==0)
make_value: Allows to copy-construct value_ptr
make_value: Allows to move-construct value_ptr (C++11)
make_value: Allows to in-place copy-construct value_ptr from arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from arguments (C++11)
make_value: Allows to in-place copy-construct value_ptr from initializer-list and arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from initializer-list and arguments (C++11)
std::hash<>: Allows to obtain hash (C++11)
```

### A.2 Hidden test cases tagged with [.applet]

Applets demonstrate a specific use case.

```
[none]
```

### A.3 Hidden test cases for compile-time information

The version of *value-ptr lite* is available via tag [.version]. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

```
value-ptr-lite version[.version]
C++ compiler: compiler version[.compiler]
C++ language: __cplusplus[.stdc++]
C++ language: nsvp_CPP11_OR_GREATER[.stdc++]
C++ language: nsvp_CPP14_OR_GREATER[.stdc++]
C++ language: nsvp_CPP17_OR_GREATER[.stdc++]
C++ language: presence of C++ language features[.stdlanguage]
C++ library: presence of C++ library features[.stdlibrary]
```
