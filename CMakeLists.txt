# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project(Examples
    DESCRIPTION "Paper examples"
    LANGUAGES CXX)

cmake_minimum_required(VERSION 3.17)

include(CheckCXXCompilerFlag)
include(CTest)

check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)

if(${HAVE_FLAG_STD_CXX20})
    set(CMAKE_CXX_STANDARD 20)
else()

check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
    
    if(${HAVE_FLAG_STD_CXX17})

        set(CMAKE_CXX_STANDARD 17)
    else()
         message( FATAL_ERROR "Your compiler needs to support at least CXX 17")
    endif()
endif()

if(${TBB_FOUND})
find_package(TBB)
else()
find_package(Threads)
endif()
find_package(HPX)
find_package(OpenMP)

add_subdirectory(src)
