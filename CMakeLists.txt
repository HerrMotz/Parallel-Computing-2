cmake_minimum_required(VERSION 3.20)
project(PC2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(single-if-ex single_if_ex.c)
add_executable(integrals integrals.cpp)

add_executable(thread_num_ex thread_num_ex.c)

add_executable(fp_example fp_ex.c)
add_executable(vec_alloc_example vec_alloc_ex.c)
add_executable(inn_prod_example inn_prod_ex.c inner_prod.h)
add_executable(mat_alloc_example mat_alloc_ex.c mat_alloc.h)

add_executable(vec_add vec_add.c vec_add.h)

add_executable(scoping_experiment_1 scoping_experiment_1.c)
add_executable(scoping_experiment_2 scoping_experiment_2.c)

add_executable(montecarlo montecarlo_serial.c)
add_executable(mc_no_false_sharing montecarlo_no_false_sharing.c)
add_executable(mc_false_sharing montecarlo_false_sharing.c)
add_executable(mc_false_sharing_fix montecarlo_false_sharing_try_fix.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -O0")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O0")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

    target_link_libraries(thread_num_ex PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(scoping_experiment_1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(scoping_experiment_2 PUBLIC OpenMP::OpenMP_CXX m)
    target_link_libraries(inn_prod_example PUBLIC OpenMP::OpenMP_CXX m)
    target_link_libraries(montecarlo PUBLIC OpenMP::OpenMP_CXX m)
    target_link_libraries(mc_no_false_sharing PUBLIC OpenMP::OpenMP_CXX m)
    target_link_libraries(mc_false_sharing PUBLIC OpenMP::OpenMP_CXX m)
    target_link_libraries(mc_false_sharing_fix PUBLIC OpenMP::OpenMP_CXX m)
endif()
