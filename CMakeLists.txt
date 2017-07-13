cmake_minimum_required(VERSION 3.7)
project(FT_P)

set(CMAKE_C_STANDARD 99)

set(SVR_SRC
        server_src/ft_abs_path.c
        server_src/ft_cd.c
        server_src/ft_check_root.c
        server_src/ft_cmd.c
        server_src/ft_get.c
        server_src/ft_get_pwd.c
        server_src/ft_ls.c
        server_src/ft_p_server.h
        server_src/ft_port.c
        server_src/ft_put.c
        server_src/ft_pwd.c
        server_src/ft_quit.c
        server_src/ft_responce.c
        server_src/server.c
        server_src/server_loop.c
        server_src/suport.c
        ft_p.h server_src/ft_mkdir.c)
set(LIB_SRC
        libft/ft_atoi.c
        libft/ft_atoi_base.c
        libft/ft_bzero.c
        libft/ft_convert.c
        libft/ft_flags.c
        libft/ft_free_str_arr.c
        libft/ft_is_newword.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_ishex.c
        libft/ft_isprint.c
        libft/ft_isspace.c
        libft/ft_itoa.c
        libft/ft_itoa_base.c
        libft/ft_lstadd.c
        libft/ft_lstaddend.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_modifiers.c
        libft/ft_newword.c
        libft/ft_nummoders.c
        libft/ft_numwords.c
        libft/ft_pad.c
        libft/ft_power.c
        libft/ft_printchar.c
        libft/ft_printf.c
        libft/ft_printnumber.c
        libft/ft_printstring.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strreplace_char.c
        libft/ft_strsplit.c
        libft/ft_strsplit_fn.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/ft_wordlen.c
        libft/get_next_line.c
        libft/libft.h)

set(CLN_SRC
        client_src/client.c
        client_src/ft_cd.c
        client_src/ft_get.c
        client_src/ft_lcd.c
        client_src/ft_lls.c
        client_src/ft_ls.c
        client_src/ft_p_client.h
        client_src/ft_port.c
        client_src/ft_put.c
        client_src/ft_pwd.c
        client_src/ft_quit.c
        client_src/ft_receve_data.c
        client_src/suport.c
        client_src/ft_cmd.c
        client_src/ft_recponce.c
        client_src/ft_lpwd.c
        client_src/ft_lmkdir.c
        client_src/ft_mkdir.c
        ft_p.h client_src/ft_search_builtin.c)

include_directories(libft)

add_executable(client ${CLN_SRC})
add_executable(server ${SVR_SRC})
add_library(libft STATIC ${LIB_SRC})

target_link_libraries(client libft)
target_link_libraries(server libft)