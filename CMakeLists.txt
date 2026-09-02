cmake_minimum_required(VERSION 3.14)
project(cpp-basic-projects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -pthread)

add_executable(m01 01_pointers_references_and_memory/main.cpp)
add_executable(m02 02_oop_and_virtual_tables/main.cpp)
add_executable(m03 03_raii_and_smart_pointers/main.cpp)
add_executable(m04 04_move_semantics_and_rvalues/main.cpp)
add_executable(m05 05_templates_and_stl_containers/main.cpp)
add_executable(m06 06_modern_cpp_lambdas_and_functional/main.cpp)
add_executable(m07 07_multithreading_and_concurrency/main.cpp)
