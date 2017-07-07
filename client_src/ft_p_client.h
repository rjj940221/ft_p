//
// Created by rojones on 2017/07/06.
//

#ifndef FT_P_CLIENT_H
# define FT_P_CLIENT_H

# include <netinet/in.h>
# include <printf.h>
# include <stdlib.h>
# include <netdb.h>
# include <memory.h>
# include <zconf.h>
# include <libft.h>
# include <sys/mman.h>
# include "../ft_p.h"
# include <libft.h>
# include <ctype.h>

# define FALSE 0
# define TRUE 1

typedef char t_bool;

typedef struct s_clt_env
{
	t_bool	wait_rsp;
	int		svr_cmd_sock;
} t_clt_env;

typedef void(*builtin)(char **argv);

typedef struct 	s_builtin_cmd
{
	char	*cmd;
	builtin	fun;
}				t_builtin_cmd;

extern t_clt_env g_clt_env;

int			check_port(const char *str);
void		ft_print_exit(char *str);
void		ft_get(char **argv);
void		ft_put(char **argv);
void		ft_ls(char **argv);
void		ft_cd(char **argv);
void		ft_pwd(char **argv);
void		ft_quit(char **argv);
t_cmd_rsp	ft_get_cmd_responce();

void 		ft_send_cmd(t_cmd cmd);

static t_builtin_cmd g_builtin_cmd[] = {
		{"ls",ft_ls},
		{"pwd",ft_pwd},
		{"cd", ft_cd},
		{"get", ft_get},
		{"put", ft_put},
		{"quit", ft_quit},
		NULL
};

#endif
