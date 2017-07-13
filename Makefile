SVR_NAME = server
CLN_NAME = client
INCLUDES = -I libft
C_FLAGS = -g3 -Wall -Werror -Wextra $(INCLUDES)
L_FLAGS = -L libft -lft
CC = gcc

SVR_SRC = server_src/ft_abs_path.c server_src/ft_get.c server_src/ft_port.c\
		  server_src/ft_responce.c server_src/ft_cd.c server_src/ft_get_pwd.c\
	  	  server_src/ft_put.c server_src/server.c server_src/ft_check_root.c\
	  	  server_src/ft_ls.c server_src/ft_pwd.c server_src/server_loop.c\
		  server_src/ft_cmd.c server_src/ft_quit.c server_src/suport.c

SVR_OBJ = build_svr/ft_abs_path.o build_svr/ft_get.o build_svr/ft_port.o\
  		  build_svr/ft_responce.o build_svr/ft_cd.o build_svr/ft_get_pwd.o\
	  	  build_svr/ft_put.o build_svr/server.o build_svr/ft_check_root.o\
	  	  build_svr/ft_ls.o build_svr/ft_pwd.o build_svr/server_loop.o\
		  build_svr/ft_cmd.o build_svr/ft_quit.o build_svr/suport.o

CLN_SRC = client_src/client.c client_src/ft_receve_data.c client_src/ft_cd.c\
		  client_src/ft_port.c client_src/ft_recponce.c client_src/ft_cmd.c\
		  client_src/ft_put.c client_src/suport.c client_src/ft_get.c\
		  client_src/ft_pwd.c client_src/ft_ls.c client_src/ft_quit.c

CLN_OBJ = build_cln/client.o build_cln/ft_receve_data.o build_cln/ft_cd.o\
  		  build_cln/ft_port.o build_cln/ft_recponce.o build_cln/ft_cmd.o\
		  build_cln/ft_put.o build_cln/suport.o build_cln/ft_get.o\
		  build_cln/ft_pwd.o build_cln/ft_ls.o build_cln/ft_quit.o

all : lft $(SVR_NAME) $(CLN_NAME)

build_svr/%.o :  server_src/%.c server_src/ft_p_server.h
	@mkdir -p build_svr
	@$(CC) $(C_FLAGS) -c $< -o $@
	@echo "\033[92m$@\033[0m"

build_cln/%.o :  client_src/%.c client_src/ft_p_client.h
	@mkdir -p build_cln
	@$(CC) $(C_FLAGS) -c $< -o $@
	@echo "\033[92m$@\033[0m"

lft:
	@echo "making libft"
	@make -C libft

$(SVR_NAME) : $(SVR_OBJ)
	@$(CC) $^ $(L_FLAGS) -o $(SVR_NAME)
	@echo "\033[92m$@\033[0m"

$(CLN_NAME) : $(CLN_OBJ)
	@$(CC) $^ $(L_FLAGS) -o $(CLN_NAME)
	@echo "\033[92m$@\033[0m"

clean:
	@\rm -rf build_svr
	@\rm -rf build_cln
	@make -C libft clean

fclean: clean
	@rm -f  $(SVR_NAME)
	@rm -f $(CLN_NAME)
	make -C libft fclean

re: fclean all
