# value-ptr lite: A C++ smart-pointer with value semantics for C++98, C++11 and later

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://travis-ci.org/martinmoene/value-ptr-lite.svg?branch=master)](https://travis-ci.org/martinmoene/value-ptr-lite) [![Build status](https://ci.appveyor.com/api/projects/status/w2dgn3fxyrd6vcq8?svg=true)](https://ci.appveyor.com/project/martinmoene/value-ptr-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fvalue-ptr-lite.svg)](https://github.com/martinmoene/value-ptr-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/value-ptr-lite/master/include/nonstd/value_ptr.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://bintray.com/martinmoene/nonstd-lite/value-ptr-lite%3Anonstd-lite/_latestVersion)


**Contents**
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Reported to work with](#reported-to-work-with)
- [Building tests and examples](#building-tests-and-examples)
- [Other value_ptr implementations](#other-value-ptr-implementations)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Pimpl example usage
-------------------

```Cpp
// in header file:

#include "nonstd/value_ptr.hpp"

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

This work is inspired on `value_ptr` by Gaetano Checinski [[1]](#ref1) and on `impl_ptr` by Andrey Upadyshev [[2]](#ref2).

**Features and properties of value-ptr lite** are ease of installation (single header), freedom of dependencies other than the standard library. *value-ptr lite* shares the approach to in-place tags with any-lite, optional-lite and with variant-lite and these libraries can be used together.

**Limitations of value-ptr lite** are ... .


License
-------
*value-ptr lite* is distributed under the [Boost Software License](LICENSE.txt).

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

| Purpose          |[[1]](#ref1) | [[2]](#ref2)| Type | Notes |
|------------------|:-----------:|:------:|------|-------|
| Smart pointer with<br>value semantics |&#10003;|&#10003;| class **value_ptr**  | [2]: impl_ptr |
| Error reporting       |&ndash; |&ndash; | class **bad_value_access**           | &nbsp; |
| In-place construction |&ndash; |&ndash; | struct **in_place_tag**              | &nbsp; |
| &nbsp;                |&ndash; |&ndash; | **in_place**                         | select type or index for in-place construction |
| &nbsp;                |&ndash; |&ndash; | **nonstd_lite_in_place_type_t**( T)  | macro for alias template in_place_type_t&lt;T>  |
| &nbsp;                |&ndash; |&ndash; | **nonstd_lite_in_place_index_t**( T )| macro for alias template in_place_index_t&lt;T> |

### Interface of *value-ptr lite*

#### Class `value_ptr`

| Kind      |[[1]](#ref1) | [[2]](#ref2)|std| Type / Method | Note / Result |
|-----------|:-----------:|:------:|--------|------------|---------------|
| Value types    |&#10003;|&#10003;| &nbsp; | **element_type**    |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | **pointer**         |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | **reference**       |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | **const_pointer**   |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | **const_reference** |&nbsp; |
| Lifetime types |&#10003;|&ndash; | &nbsp; | **cloner_type**     |[2]: copier_type |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | **deleter_type**    |&nbsp; |
| Construction   |&#10003;|&#10003;| &nbsp; | **value_ptr**() noexcept |&nbsp; |
| &nbsp;         |&ndash; |&#10003;| C++11  | **value_ptr**( std::nullptr_t ) noexcept|&nbsp; |
| &nbsp;         |&#10003;|&ndash; | &nbsp; | **value_ptr**( pointer p ) noexcept |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | **value_ptr**( value_ptr const & other ) |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| C++11  | **value_ptr**( value_ptr && other ) noexcept |&nbsp; |
| &nbsp;         |&#10003;|    1   | &nbsp; | **value_ptr**( element_type const & value ) |&nbsp; |
| &nbsp;         |&#10003;|    1   | C++11  | **value_ptr**( element_type && value ) noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | template< class... Args ><br>explicit **value_ptr**( in_place_type_t(T), Args&&... args ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | template< class U, class... Args ><br>explicit **value_ptr**( in_place_type_t(T), std::initializer_list&lt;U> il, Args&&... args ) |&nbsp; |
| &nbsp;         |&#10003;|&ndash; | &nbsp; | **value_ptr**( cloner_type const & cloner ) |&nbsp; |
| &nbsp;         |&#10003;|&ndash; | C++11  | **value_ptr**( cloner_type && cloner ) noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | **value_ptr**( deleter_type const & deleter ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | **value_ptr**( deleter_type && deleter ) noexcept |&nbsp; |
| &nbsp;         |&#10003;|&ndash; | C++11  | template< class V, class ClonerOrDeleter ><br>**value_ptr**( V && value, ClonerOrDeleter && cloner_or_deleter ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; |<C++11  | template< class V, class ClonerOrDeleter ><br>**value_ptr**( V const & value, ClonerOrDeleter const & cloner_or_deleter ) |&nbsp; |
| &nbsp;         |&#10003;|&ndash; | C++11  | template< class V, class C, class D ><br>**value_ptr**( V && value, C && cloner, D && deleter ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; |<C++11  | template< class V, class C, class D ><br>**value_ptr**( V const & value, C const & cloner, D const & deleter ) |&nbsp; |
| Destruction    |&ndash; |&ndash; | C++11  | **~value_ptr**() |&nbsp; |
| Assignment     |&ndash; |&ndash; | C++11  | value_ptr & **operator=**( std::nullptr_t ) noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | value_ptr & **operator=**( T const & value ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | template< class U, ... ><br>value_ptr & **operator=**( U && value ) |&nbsp; |
| &nbsp;         |&ndash; |&#10003;| &nbsp; | value_ptr & **operator=**( value_ptr const & rhs ) |&nbsp; |
| &nbsp;         |&ndash; |&#10003;| C++11  | value_ptr & **operator=**( value_ptr && rhs ) noexcept |&nbsp; |
| Emplace        |&ndash; |&ndash; | C++11  | template< class... Args ><br>void **emplace**( Args&&... args ) |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | template< class U, class... Args ><br>void **emplace**( std::initializer_list&lt;U> il, Args&&... args ) |&nbsp; |
| Observers      |&#10003;|&#10003;| &nbsp; | pointer **get**() noexcept |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | cloner_type & **get_cloner**() noexcept |[2]: get_copier() |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | deleter_type & **get_deleter**() noexcept |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | reference **operator\***() const |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| &nbsp; | pointer **operator->**() const noexcept |&nbsp; |
| &nbsp;         |&#10003;|&#10003;| C++11  | explicit operator **bool**() const noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; |<C++11  | operator **safe_bool**() const noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | bool **has_value**() const nsvp_noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | element_type const & **value**() const |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | element_type & **value**() |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | C++11  | template< class U ><br>constexpr element_type **value_or**( U && v ) const |&nbsp; |
| &nbsp;         |&ndash; |&ndash; |<C++11  | template< class U ><br>constexpr element_type **value_or**( U const & v ) const |&nbsp; |
| Modifiers      |&#10003;|&#10003;| &nbsp; | pointer **release**() noexcept |&nbsp; |
| &nbsp;         |&ndash; |&ndash; | &nbsp; | void **reset**( pointer p = pointer() ) noexcept |&nbsp; |
| &nbsp;         |&ndash; |&#10003;| &nbsp; | void **swap**( value_ptr & other ) noexcept |&nbsp; |

**Notes:**<br>
1. [2] has various converting constructors.

### Non-member functions for *value-ptr lite*

| Kind                 |[[1]](#ref1)| [[2]](#ref2)| std  | Function |
|--------------------------|:------:|:------:|:----:|----------|
| Relational operators     |&ndash; |&#10003;|&nbsp;| template< ... ><br>bool operator **_op_**( value_ptr<...> const & lhs, value_ptr<...> const & rhs ) |
| &nbsp;                   |&ndash; |&#10003;|C++11 | template< ... ><br>bool operator **_op_**( value_ptr<...> const & lhs, std::nullptr_t ) |
| &nbsp;                   |&ndash; |&#10003;|C++11 | template< ... ><br>bool operator **_op_**( std::nullptr_t, value_ptr<...> const & rhs ) |
| &nbsp;                   |&ndash; |&ndash; |&nbsp;| template< ... ><br>bool operator **_op_**( value_ptr<...> const & lhs, T const & value ) |
| &nbsp;                   |&ndash; |&ndash; |&nbsp;| template< ... ><br>bool operator **_op_**( T const & value, value_ptr<...> const & rhs ) |
| Swap                     |&ndash; |&#10003;|&nbsp;| template< class T, class C, class D ><br>void **swap**( value_ptr&lt;T,C,D> & x, value_ptr&lt;T,C,D> & y ) noexcept(...) |
| Create                   |&ndash; |&ndash; |<C++11| template< class T, class C, class D ><br>value_ptr&lt;T,C,D> **make_value**( T const & v )      |
| &nbsp;                   |&ndash; |&ndash; | C++11| template< class T ><br>value_ptr< typename std::decay&lt;T>::type > **make_value**( T && v ) |
| &nbsp;                   |&ndash; |&ndash; | C++11| template< class T, class...Args ><br>value_ptr&lt;T,C,D> **make_value**( Args&&... args ) |
| &nbsp;                   |&ndash; |&ndash; | C++11| template< class T, class U, class... Args ><br>value_ptr&lt;T,C,D> **make_value**( std::initializer_list&lt;U> il, Args&&... args ) |
| Hash                     |&ndash; |&#10003;| C++11| template< class T ><br>class **hash**< nonstd::value_ptr&lt;T,C,D> > |


### Configuration macros

#### Compare pointers
-D<b>nsvp_CONFIG_COMPARE_POINTERS</b>=0
Define this to 1 to compare `value_ptr`'s pointer instead of the content it's pointing to. Default is 0.

#### Disable exceptions
-D<b>nsvp_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.


Reported to work with
---------------------
The table below mentions the compiler versions *value-ptr lite* is reported to work with.

OS        | Compiler   | Versions |
---------:|:-----------|:---------|
Windows   | Clang/LLVM | ? |
&nbsp;    | GCC        | 5.2.0, 6.3.0 |
&nbsp;    | Visual C++<br>(Visual Studio)| 8 (2005), 10 (2010), 11 (2012),<br>12 (2013), 14 (2015, 2017) |
GNU/Linux | Clang/LLVM | 3.1.0 - 4.0.0 (Wandbox) |
&nbsp;    | GCC        | 4.4.7 - 7.1.0 (Wandbox) |
OS X      | ?          | ?   |


Building tests and examples
---------------------------
To build the tests and examples you need:

- [Buck](https://buckbuild.com/) or [CMake](http://cmake.org) version 2.8.12 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with).

The [*lest* test framework](https://github.com/martinmoene/lest)  is included in the [test folder](test).

The following steps assume that the [*value_ptr lite* source code](https://github.com/martinmoene/value-ptr-lite) has been cloned into a directory named `value-ptr-lite`.

### Buck

To run the tests and examples:
```
value-ptr-lite> buck run test
value-ptr-lite> buck run example:01-pimpl
value-ptr-lite> buck run example:02-tree
```

### CMake

1. Create a directory for the build outputs for a particular architecture.
Here we use `value-ptr-lite/build`.

        value-ptr-lite> mkdir build && cd build

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        value-ptr-lite/build> cmake -G "Unix Makefiles" [see 3. below] ..

3. Optional. You can control above configuration through the following options:
   - `-DVALUE_PTR_LITE_BUILD_TEST=ON`: build the tests for lest, default off
   - `-DVALUE_PTR_LITE_BUILD_EXAMPLE=ON`: build the examples, default off
   - `-DVALUE_PTR_LITE_COLOURISE_TEST=ON`: use colour for pass, fail, default off

4. Build the test suite. With Visual Studio, append the configuration as `--config Debug` or `--config Release`.

        value-ptr-lite/build> cmake --build .

5. Run the test suite.

        value-ptr-lite/build> ctest -V

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

### A.1 Compile-time information

The version of *value-ptr lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 Value-ptr lite test specification

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
value_ptr: Allows to obtain engaged state via has_value()
value_ptr: Allows to obtain value via value()
value_ptr: Allows to obtain value or default via value_or()
value_ptr: Allows to obtain moved-default via value_or() (C++11)
value_ptr: Throws bad_value_access at disengaged access
value_ptr: Allows to release its content
value_ptr: Allows to clear its content (reset)
value_ptr: Allows to replace its content (reset)
value_ptr: Allows to swap with other value_ptr (member)
value_ptr: Allows to swap with other value_ptr (non-member)
value_ptr: Provides relational operators (non-member, pointer comparison: nsvp_CONFIG_COMPARE_POINTERS!=0)
value_ptr: Provides relational operators (non-member, value comparison: nsvp_CONFIG_COMPARE_POINTERS==0)
value_ptr: Provides relational operators (non-member, mixed value comparison: nsvp_CONFIG_COMPARE_POINTERS==0)
make_value: Allows to copy-construct value_ptr
make_value: Allows to move-construct value_ptr (C++11)
make_value: Allows to in-place copy-construct value_ptr from arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from arguments (C++11)
make_value: Allows to in-place copy-construct value_ptr from initializer-list and arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from initializer-list and arguments (C++11)
std::hash<>: Allows to obtain hash (C++11)
```
