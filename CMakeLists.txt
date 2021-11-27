cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/readline)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)

FILE(GLOB SRC
        "main.c"
        "buildins/*.c"
        "utils/*.c"
        "srcs/*.c"
        "pipe/*.c")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(minishell ${SRC})
target_link_libraries (minishell ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.a)
target_link_libraries (minishell readline)
