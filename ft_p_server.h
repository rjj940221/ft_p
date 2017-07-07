#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "ft_p.h"
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

typedef struct		s_svr_env
{
	int 			cln_cmd;
	int 			svr_id;
	char 			*svrroot;
	char 			*home;
	t_tcp_sock_in	sock_in;
}					t_svr_env;

extern t_svr_env	g_svr_env;
void ft_print_exit(char *str);
t_cmd	ft_get_cmd();
#endif
