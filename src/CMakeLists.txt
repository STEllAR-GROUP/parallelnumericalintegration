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
    add_test(NAME "HPX:_Taylor_Par" COMMAND taylor_par_hpx 100 0.5)
    add_hpx_executable(taylor_future_hpx SOURCES taylor_future_hpx.cpp)
    add_test(NAME "HPX:_Taylor_Future" COMMAND taylor_future_hpx 100 0.5 3)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_hpx_executable(taylor_future_coroutine_hpx SOURCES taylor_future_coroutine_hpx.cpp)
        add_test(NAME "HPX:_Taylor_Future_Coroutine" COMMAND taylor_future_coroutine_hpx 100 0.5 3)
    endif()


    if(${HAVE_FLAG_STD_CXX20})
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 10)
            add_hpx_executable(taylor_future_coroutine_hpx SOURCES taylor_future_coroutine_hpx.cpp)
            add_test(NAME "HPX:_Taylor_Future_Coroutine" COMMAND taylor_future_coroutine_hpx 100 0.5 3)
            target_compile_options(taylor_future_coroutine_hpx PUBLIC "-fcoroutines")
            endif()
        endif()  
        #add_hpx_executable(taylor_sender_receiver_hpx SOURCES taylor_sender_receiver_hpx.cpp)
        #add_test(NAME "HPX:_Taylor_Sender_Receiver" COMMAND taylor_sender_receiver_hpx 100 0.5 3)
    endif()
endif()

add_executable(taylor_future taylor_future.cpp)
target_link_libraries(taylor_future PRIVATE Threads::Threads)
add_test(NAME "Parallel:_Taylor_future" COMMAND taylor_future 100 0.5 3)

if(NOT APPLE AND "${FOUND_OPENMP}")
   add_executable(taylor_par_openmp taylor_par_openmp.cpp)
   target_compile_options(taylor_par_openmp PUBLIC "${OpenMP_CXX_FLAGS}" )
   target_link_libraries(taylor_par_openmp PUBLIC OpenMP::OpenMP_CXX)
   add_test(NAME "OpenMP:_Taylor" COMMAND taylor_par_openmp) 
endif()
