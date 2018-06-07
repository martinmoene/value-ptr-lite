# Copyright 2017-2018 by Martin Moene
#
# https://github.com/martinmoene/value_ptr-lite
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )

project( examples )

set( TARGETS
    01-pimpl
    02-tree
)

set( HDRDIR ${PROJECT_SOURCE_DIR}/../include/nonstd )

foreach( target ${TARGETS} )
    add_executable( ${target} ${target}.cpp )
endforeach()

# set compiler options:

if( CMAKE_CXX_COMPILER_ID MATCHES MSVC )
    foreach( target ${TARGETS} )
        target_compile_options( ${target} PUBLIC -W3 -EHsc )
    endforeach()
else()
    foreach( target ${TARGETS} )
        target_compile_options( ${target} PUBLIC -std=c++11 -Wall -Wno-missing-braces )
    endforeach()
endif()

foreach( target ${TARGETS} )
    target_compile_options( ${target} PUBLIC -Dlest_FEATURE_AUTO_REGISTER=1 )
    target_include_directories( ${target} PRIVATE ${HDRDIR} )
endforeach()

# configure unit tests via CTest:

enable_testing()

foreach( target ${TARGETS} )
    add_test    ( NAME ${target} COMMAND ${target} )
    set_property( TEST ${target} PROPERTY LABELS test example )
endforeach()

# end of file