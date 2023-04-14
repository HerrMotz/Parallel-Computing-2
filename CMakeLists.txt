cmake_minimum_required(VERSION 3.23)
project(PC2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(fp_example fp_ex.c)
add_executable(vec_alloc_example vec_alloc_ex.c)
add_executable(inn_prod_example inn_prod_ex.c inner_prod.h)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    target_link_libraries(fp_example PUBLIC OpenMP::OpenMP_CXX)
endif()

