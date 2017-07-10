cmake_minimum_required(VERSION 3.7)
project(FT_P)

set(CMAKE_C_STANDARD 99)

aux_source_directory(server_src SVR_SRC)
aux_source_directory(client_src CLT_SRC)
aux_source_directory(libft LIBFT_SRC)
#set(SERVER_SOURCE_FILES server_src/server.c ft_p_server.h ft_p.h)
#set(CLIENT_SOURCE_FILES client_src/client.c ft_p.h)

include_directories(${CMAKE_SOURCE_DIR}/libft)
add_library(libft STATIC ${LIBFT_SRC})

add_executable(client ${CLT_SRC})
target_link_libraries(client libft)
add_executable(server ${SVR_SRC} server_src/ft_put.c)
target_link_libraries(server libft)