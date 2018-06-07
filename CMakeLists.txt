# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/value_ptr-lite
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )

# At default, enable building and performing of tests and building of examples:

option( VALUE_PTR_LITE_BUILD_TEST    "Build and perform value_ptr-lite tests" ON )
option( VALUE_PTR_LITE_BUILD_EXAMPLE "Build value_ptr-lite examples" ON )

project( value_ptr_lite )

set( package_name "value_ptr-lite" )
set( include_source_dir "${PROJECT_SOURCE_DIR}/include" )

# Interface library:

add_library(                
    ${package_name} INTERFACE )
    
target_include_directories( 
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

enable_testing()

if ( VALUE_PTR_LITE_BUILD_TEST )
    add_subdirectory( test )
endif()

if ( VALUE_PTR_LITE_BUILD_EXAMPLE )
    add_subdirectory( example )
endif()

# end of file
