cmake_minimum_required(VERSION 3.7)
project(FT_P)

set(CMAKE_C_STANDARD 99)

set(SERVER_SOURCE_FILES server_src/server.c ft_p_server.h ft_strsplit_fn.c ft_p.h)

set(CLIENT_SOURCE_FILES client_src/client.c ft_strsplit_fn.c ft_p.h ft_p_client.h client_src/suport.c client_src/ft_put.c client_src/ft_cmd_chanle.c)

AUX_SOURCE_DIRECTORY(libft LIBFT_SOURCE)

add_library(libft STATIC ${LIBFT_SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/libft)
link_directories(${CMAKE_SOURCE_DIR}/libft)

add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client libft)
add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server libft)