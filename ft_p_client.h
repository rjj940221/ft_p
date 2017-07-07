//
// Created by rojones on 2017/07/06.
//

#ifndef FT_P_CLIENT_H
#define FT_P_CLIENT_H
#include <stdlib.h>
#include <netdb.h>
#include <memory.h>
#include <zconf.h>
#include "../libft/libft.h"
#include <sys/mman.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <printf.h>
#include "ft_p.h"

typedef struct  s_client_env
{
	int		svr_sock;
}				t_clt_env;

typedef struct	s_cmd
{
	char	*cmd;
	char	**av;
}				t_cmd;

extern t_clt_env g_clt_env;

int check_port(const char *str);
void error_exit(const char *str);

#endif
