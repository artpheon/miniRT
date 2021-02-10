cmake_minimum_required(VERSION 3.17)
project(miniRT C)

set(CMAKE_C_STANDARD 99)

add_executable(miniRT
        src/main.c
        src/conf_parser/parser.c
        src/geom/geom.c
        src/mlx/mlx_head.c
        src/testing/test.c
        src/utils/utils.c)