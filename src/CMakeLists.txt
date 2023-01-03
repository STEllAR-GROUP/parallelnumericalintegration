# Copyright (c) 2022 AUTHORS
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(${TBB_FOUND})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
        message(FATAL_ERROR "GCC version must be at least 9.0 for the parallel algorithms!")
    endif()

    add_executable(taylor_cpp taylor_par.cpp)
    add_test(NAME "Taylor_cpp" COMMAND taylor_cpp 100 0.5)
    target_link_libraries(taylor_cpp PUBLIC TBB::tbb)
    target_compile_options(taylor_cpp PRIVATE -std=c++1z)
endif()
endif()

if(${HPX_FOUND})
    add_hpx_executable(taylor_par_hpx SOURCES taylor_par_hpx.cpp)
    add_test(NAME "HPX:_Taylor" COMMAND taylor_par_hpx 100 0.5)
endif()
