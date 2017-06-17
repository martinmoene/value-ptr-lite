# Copyright (c) 2017 Martin Moene
#
# https://github.com/martinmoene/value-ptr-lite
#
# This code is licensed under the MIT License (MIT).

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
