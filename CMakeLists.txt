cmake_minimum_required(VERSION 4.2)
project(chttpserver C)

set(CMAKE_C_STANDARD 11)

add_executable(chttpserver
        main.c)

add_custom_command(TARGET chttpserver POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/index.html"
        "${CMAKE_CURRENT_BINARY_DIR}/index.html"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/jeff"
        "${CMAKE_CURRENT_BINARY_DIR}/jeff"
)