/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_client.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 10:04:52 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 10:05:36 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_CLIENT_H
# define FT_P_CLIENT_H

# include <netinet/in.h>
# include <printf.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <netdb.h>
# include <memory.h>
# include <zconf.h>
# include <libft.h>
# include <sys/mman.h>
# include <arpa/inet.h>
# include "../ft_p.h"
# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <printf.h>
# include <stdio.h>
# include <sys/param.h>
# include <sys/errno.h>


typedef struct s_clt_env
{
	t_bool	wait_rsp;
	int		svr_cmd_sock;
	int 	data_sock;
	int 	data_chanle;
} t_clt_env;

typedef void(*builtin)(char **argv);

typedef struct 	s_builtin_cmd
{
	char	*cmd;
	builtin	fnc;
}				t_builtin_cmd;

extern t_clt_env g_clt_env;

int			check_port(const char *str);
void		ft_print_exit(char *str);
void		ft_get(char **argv);
void		ft_put(char **argv);
void 		ft_lls(char **argv);
void		ft_ls(char **argv);
void		ft_cd(char **argv);
void		ft_pwd(char **argv);
void 		ft_lcd(char **argv);
void		ft_lpwd(char **argv);
void		ft_quit(char **argv);
void 		ft_port(int port);
t_cmd_rsp	*ft_get_cmd_responce();
void		ft_cmd_responce_dell(t_cmd_rsp **rsp);
void		ft_close_data_sock();
void 		ft_process_rsp(t_cmd_rsp	rsp);
char		*ft_get_addr_str(int sock_id);
void 		ft_send_cmd(t_cmd cmd);
size_t		ft_receve_data(char **data);
void 		ft_data_connection();
char		*ft_get_pwd(void);
t_bool		ft_check_eol(char buf[2], unsigned char *r);



static t_builtin_cmd g_builtin_cmd[] = {
		{"lls", ft_lls},
		{"ls", ft_ls},
		{"lpwd", ft_lpwd},
		{"pwd",ft_pwd},
		{"lcd", ft_lcd},
		{"cd", ft_cd},
		{"get", ft_get},
		{"put", ft_put},
		{"quit", ft_quit},
		{NULL, NULL}
};

#endif
