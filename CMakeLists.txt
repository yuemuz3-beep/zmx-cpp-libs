cmake_minimum_required(VERSION 3.28)
project(zmx-cpp-libs)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/bigint)

add_executable(bigint_demo examples/bigint/bigint_demo.cpp)

target_link_libraries(bigint_demo PRIVATE bigint)

add_executable(normalize_test
        tests/bigint/normalize_test.cpp
)