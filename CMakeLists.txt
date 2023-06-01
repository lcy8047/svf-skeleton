cmake_minimum_required(VERSION 3.4.3)

set( CMAKE_OSX_ARCHITECTURES "x86_64" )

project( svf-skeleton VERSION 1.0 )

if ( DEFINED LLVM_DIR )
    set( ENV{LLVM_DIR} "${LLVM_DIR}" )
endif()

if ( DEFINED ENV{LLVM_DIR} )
    # We need to match the build environment for LLVM:
    # In particular, we need C++11 and the -fno-rtti flag
    set( CMAKE_CXX_STANDARD 14 )
    set( CMAKE_CXX_FLAGS "-fPIC -std=gnu++14 -O3 -fno-rtti -Wno-deprecated" )
    set( CMAKE_C_FLAGS "-fPIC" )

    # ref : https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
    find_package( LLVM REQUIRED CONFIG )

    list( APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}" )
    include( AddLLVM )

    add_definitions( ${LLVM_DEFINITIONS} )
    include_directories( ${LLVM_INCLUDE_DIRS} )

else()
    message( FATAL_ERROR "The LLVM_DIR var was not set" )
endif()

if ( NOT EXISTS "${SVF_DIR}" )
    set( SVF_DIR $ENV{SVF_DIR} )
    if( NOT EXISTS "${SVF_DIR}" )
        message( FATAL_ERROR "WARNING: The SVF_DIR var was not set" )
    endif()
endif()

set(SVF_HEADER "${SVF_DIR}/svf/include")
set(SVF_LLVM_HEADER "${SVF_DIR}/svf-llvm/include")
set(SVF_LIB "${SVF_DIR}/Debug-build/svf-llvm/libSvfLLVM.a")
set(SVF_BIN_HEADER "${SVF_DIR}/Debug-build/include")
include_directories(${SVF_HEADER}
                    ${SVF_LLVM_HEADER}
                    ${SVF_BIN_HEADER})

if ( DEFINED Z3_DIR )
    set( ENV{Z3_DIR} "${Z3_DIR}" )
endif()
find_library( Z3_LIBRARIES NAMES libz3.a libz3.so
            HINTS $ENV{Z3_DIR}
            PATH_SUFFIXES bin )
find_path( Z3_INCLUDES NAMES z3++.h
            HINTS $ENV{Z3_DIR}
            PATH_SUFFIXES include z3 )
if ( NOT Z3_LIBRARIES OR NOT Z3_INCLUDES )
    message( FATAL_ERROR "Z3 not found!" )
endif()
include_directories( ${Z3_INCLUDES} )
LINK_DIRECTORIES( ${Z3_DIR}/bin )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_subdirectory( lib )

add_executable( main main.cpp )
target_compile_options( main PUBLIC -g -Wall )
target_link_libraries( main TestLib )
set_target_properties( main PROPERTIES
                       RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )