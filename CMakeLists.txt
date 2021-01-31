cmake_minimum_required(VERSION 3.17)
project(miniRT C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -I${CMAKE_SOURCE_DIR}/libs/opengl/ -L${CMAKE_SOURCE_DIR}/libs/opengl/ -framework OpenGL -framework AppKit")

include_directories(${CMAKE_SOURCE_DIR}/headers/
        ${CMAKE_SOURCE_DIR}/src/conf_parser/
        ${CMAKE_SOURCE_DIR}/src/mlx/
        ${CMAKE_SOURCE_DIR}/src/testing/
        ${CMAKE_SOURCE_DIR}/src/geom/
        ${CMAKE_SOURCE_DIR}/libs/libft/
        ${CMAKE_SOURCE_DIR}/libs/mms/
        ${CMAKE_SOURCE_DIR}/libs/opengl/)

link_directories(${CMAKE_SOURCE_DIR}/headers/
        ${CMAKE_SOURCE_DIR}/src/conf_parser/
        ${CMAKE_SOURCE_DIR}/src/mlx/
        ${CMAKE_SOURCE_DIR}/src/testing/
        ${CMAKE_SOURCE_DIR}/src/geom/
        ${CMAKE_SOURCE_DIR}/libs/libft/
        ${CMAKE_SOURCE_DIR}/libs/mms/
        ${CMAKE_SOURCE_DIR}/libs/opengl/)



add_executable( miniRT
        headers/header.h
        src/conf_parser/parser.c
        libs/opengl/mlx.h   libs/opengl/libmlx.a
        src/mlx/mlx_head.c  src/mlx/mlx_head.h
        src/testing/test.c  src/testing/test.h
        src/geom/geom.c     src/geom/geom.h
        src/main.c)
target_link_libraries(  miniRT LINK_PUBLIC
                        m
                        ${CMAKE_SOURCE_DIR}/libs/opengl/libmlx.a
                        ${CMAKE_SOURCE_DIR}/libs/libft/libft.a)
