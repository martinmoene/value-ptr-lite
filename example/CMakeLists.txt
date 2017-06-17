# Copyright 2017 by Martin Moene
#
# https://github.com/martinmoene/value-ptr-lite
#
# This code is licensed under the MIT License (MIT).

cmake_minimum_required( VERSION 2.8 )

project( examples )

set( TARGETS
    01-pimpl
    02-tree
)

foreach( name ${TARGETS} )
    add_executable( ${name} ${name}.cpp )
endforeach()

# set compiler options:

if( CMAKE_CXX_COMPILER_ID MATCHES MSVC )
    foreach( name ${TARGETS} )
        target_compile_options( ${name} PUBLIC -W3 -EHsc )
    endforeach()
else()
    foreach( name ${TARGETS} )
        target_compile_options( ${name} PUBLIC -std=c++11 -Wall -Wno-missing-braces )
    endforeach()
endif()

foreach( name ${TARGETS} )
    target_compile_options( ${name} PUBLIC -Dlest_FEATURE_AUTO_REGISTER=1 )
endforeach()

# configure unit tests via CTest:

enable_testing()

foreach( name ${TARGETS} )
    add_test    ( NAME ${name} COMMAND ${name} )
    set_property( TEST ${name} PROPERTY LABELS test example )
endforeach()

# end of file
