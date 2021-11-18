cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c buildins/pwd.c includes/minishell.h buildins/main.c buildins/ft_cd.c buildins/ft_echo.c buildins/ft_env.c libft/ft_lstfind.c buildins/export.c buildins/unset.c libft/ft_lstremove.c)
