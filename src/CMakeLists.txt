
if(${TBB_FOUND})

    add_executable(taylor_cpp taylor_par.cpp)
    add_test(NAME "Taylor_cpp" COMMAND taylor_cpp 100 0.5)
    target_link_libraries(taylor_cpp PUBLIC TBB::tbb)
    target_compile_options(taylor_cpp PRIVATE -std=c++1z)
endif()
