add_library(bigint STATIC bigint.cpp)

target_include_directories(bigint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})