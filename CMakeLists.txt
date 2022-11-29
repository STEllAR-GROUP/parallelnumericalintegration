# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

project(Examples
    DESCRIPTION "Paper examples"
    LANGUAGES CXX)

cmake_minimum_required(VERSION 3.17)

include(CTest)

find_package(TBB)
find_package(HPX)

add_subdirectory(src)
