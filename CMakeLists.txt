cmake_minimum_required(VERSION 3.7)
project(FT_P)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -g3)
aux_source_directory(server_src SVR_SRC)
aux_source_directory(client_src CLT_SRC)
aux_source_directory(libft LIBFT_SRC)

include_directories(${CMAKE_SOURCE_DIR}/libft)
add_library(libft STATIC ${LIBFT_SRC} libft/ft_strreplace_char.c)

add_executable(client ${CLT_SRC} client_src/ft_port.c)
target_link_libraries(client libft)
add_executable(server ${SVR_SRC} server_src/ft_cd.c server_src/ft_check_root.c server_src/ft_get_pwd.c server_src/ft_abs_path.c server_src/ft_port.c)
target_link_libraries(server libft)