cmake_minimum_required(VERSION 3.7)
project(FT_P)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -g3)
aux_source_directory(server_src SVR_SRC)
aux_source_directory(client_src CLT_SRC)
aux_source_directory(libft LIBFT_SRC)

include_directories(${CMAKE_SOURCE_DIR}/libft)
add_library(libft STATIC ${LIBFT_SRC})

add_executable(client ${CLT_SRC})
target_link_libraries(client libft)
add_executable(server ${SVR_SRC})
target_link_libraries(server libft)