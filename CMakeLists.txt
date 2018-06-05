# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/value-ptr-lite
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 2.8.12 )

project( value_ptr_lite )

option( VALUE_PTR_LITE_BUILD_TEST     "Build tests" ON )
option( VALUE_PTR_LITE_BUILD_EXAMPLE  "Build examples" ON )

include_directories( "include/nonstd" )

if ( VALUE_PTR_LITE_BUILD_TEST )
  add_subdirectory( test )
endif()

if ( VALUE_PTR_LITE_BUILD_EXAMPLE )
  add_subdirectory( example )
endif()

enable_testing()

# end of file
