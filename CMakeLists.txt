cmake_minimum_required(VERSION 3.19)
project(pipex C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(libft)

#add_executable(pipex src/main.c src/main_utils.c src_bonus/main_bonus.c src_bonus/util_bonus.c includes/pipex_bonus.h src_bonus/execution_bonus.c)

add_executable(pipex src_bonus/main_bonus.c src_bonus/execution_bonus.c src_bonus/get_next_line_bonus.c src_bonus/util_bonus.c)


target_link_libraries(pipex libft)