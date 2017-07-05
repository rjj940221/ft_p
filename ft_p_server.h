#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "ft_p.h"

# define MAX_CLIENTS 10


typedef struct sockaddr_in
					t_tcp_sock_in;
typedef struct		s_svr_env
{
	char	*path;
	char 	*svrroot;
	char 	*home;
}					t_svr_env;

extern t_svr_env	g_svr_env;

#endif
