#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../ft_p.h"
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <libft.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/mman.h>

# define MAX_CLIENTS 10


typedef struct sockaddr_in	t_tcp_sock_in;

typedef void(*builtin)(t_cmd cmd);

typedef struct	s_builtin_cmd
{
	char 	*cmd;
	builtin	fnc;
}				t_builtin_cmd;

typedef struct		s_svr_env
{
	int 			cln_cmd;
	int 			svr_id;
	char 			*svrroot;
	t_tcp_sock_in	sock_in;
}					t_svr_env;

extern t_svr_env	g_svr_env;

int check_port(const char *str);
void	ft_send_responce(t_cmd_rsp res);
t_cmd_rsp ft_get_responce();
void ft_send_cmd(t_cmd cmd);
void ft_print_exit(char *str);

void ft_quit(t_cmd cmd);
void ft_put(t_cmd cmd);

t_cmd	ft_get_cmd();

static t_builtin_cmd g_builtin_cmd[] = {
		{"QUIT", ft_quit},
		NULL
};
#endif
