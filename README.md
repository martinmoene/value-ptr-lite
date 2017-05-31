# value-ptr lite
The last C++ smart-pointer for C++98, C++11 and later

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-98-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-14-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/martinmoene/value-ptr-lite.svg?branch=master)](https://travis-ci.org/martinmoene/value-ptr-lite) [![Build status](https://ci.appveyor.com/api/projects/status/w2dgn3fxyrd6vcq8?svg=true)](https://ci.appveyor.com/project/martinmoene/value-ptr-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fvalue-ptr-lite.svg)](https://github.com/martinmoene/value-ptr-lite/releases) [![download](https://img.shields.io/badge/latest%20version%20%20-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/value-ptr-lite/master/include/nonstd/value_ptr.hpp)

- Gaetano Checinski. [value_ptr — The Missing C++ Smart-pointer](https://hackernoon.com/value-ptr-the-missing-c-smart-pointer-1f515664153e) ([GitHub](https://github.com/LoopPerfect/valuable)). May 2017.
- Andrey Upadyshev. [PIMPL, Rule of Zero and Scott Meyers](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html) ([GitHub](https://github.com/oliora/samples/blob/master/spimpl.h)). December 29, 2015.

Appendix
--------

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
value_ptr: Allows to assign nullptr to disengage
value_ptr: Allows to copy-assign from/to engaged and disengaged value_ptr-s
value_ptr: Allows to move-assign from/to engaged and disengaged value_ptr-s (C++11)
value_ptr: Allows to copy-assign from literal value
value_ptr: Allows to copy-assign from value
value_ptr: Allows to move-assign from value (C++11)
value_ptr: Allows to copy-emplace content from arguments (C++11)
value_ptr: Allows to move-emplace content from arguments (C++11)
value_ptr: Allows to copy-emplace content from intializer-list and arguments (C++11)
value_ptr: Allows to move-emplace content from intializer-list and arguments (C++11)
value_ptr: Allows to obtain pointer to value via operator->()
value_ptr: Allows to obtain value via operator*()
value_ptr: Allows to obtain moved-value via operator*()
value_ptr: Allows to obtain engaged state via operator bool()
value_ptr: Allows to reset content
value_ptr: Allows to swap with other value_ptr (member)
value_ptr: Allows to swap with other value_ptr (non-member)
value_ptr: Provides relational operators (pointer comparison, non-member)
make_value: Allows to copy-construct value_ptr
make_value: Allows to move-construct value_ptr (C++11)
make_value: Allows to in-place copy-construct value_ptr from arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from arguments (C++11)
make_value: Allows to in-place copy-construct value_ptr from initializer-list and arguments (C++11)
make_value: Allows to in-place move-construct value_ptr from initializer-list and arguments (C++11)
std::hash<>: Allows to obtain hash (C++11)
```
