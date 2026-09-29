add_library(decimal
        decimal.cpp
)

target_include_directories(decimal PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(decimal PUBLIC bigint)