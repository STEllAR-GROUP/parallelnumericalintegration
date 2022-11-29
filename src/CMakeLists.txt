
if(${TBB_FOUND})
    add_executable(taylor_cpp taylor_par.cpp)
    add_test(NAME "Taylor_cpp" COMMAND taylor_cpp 100 0.5)
    target_link_libraries(taylor_cpp PUBLIC TBB::tbb)
    target_compile_options(taylor_cpp PRIVATE -std=c++1z)
endif()

if(${HPX_FOUND})
    add_hpx_executable(taylor_hpx SOURCES taylor_hpx.cpp)
    add_test(NAME "HPX:_Taylor" COMMAND taylor_hpx 100 0.5)
endif()
