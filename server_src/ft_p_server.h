/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_server.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:05:48 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:10:14 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include "../ft_p.h"
# include <sys/param.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>

# define MAX_CLIENTS 10

typedef struct sockaddr_in	t_tcp_sock_in;

typedef void(*t_builtin)(t_cmd cmd);

typedef struct				s_builtin_cmd
{
	char		*cmd;
	t_builtin	fnc;
}							t_builtin_cmd;

typedef struct				s_svr_env
{
	int				cln_cmd;
	int				cln_data;
	int				svr_id;
	char			*svrroot;
	t_tcp_sock_in	sock_in;
	t_conn			data_conn;
}							t_svr_env;

extern t_svr_env			g_svr_env;

int							check_port(const char *str);
t_bool						ft_check_eol(char buf[2], unsigned char *r);
void						ft_send_responce(t_cmd_rsp res);
t_cmd_rsp					ft_get_responce();
void						ft_send_cmd(t_cmd cmd);
void						ft_print_exit(char *str);
void						server_loop();
t_cmd_rsp					ft_get_responce();
void						ft_send_cmd(t_cmd cmd);
void						ft_send_responce(t_cmd_rsp res);
void						ft_print_exit(char *str);
int							check_port(const char *str);
char						*ft_get_pwd();
char						*ft_abspath(char *str);
char						*ft_check_root(char *str, int flags);
void						ft_connect_g_conn();
void						ft_cd(t_cmd cmd);
void						ft_quit(t_cmd cmd);
void						ft_put(t_cmd cmd);
void						ft_port(t_cmd cmd);
void						ft_ls(t_cmd cmd);
void						ft_pwd(t_cmd cmd);
void						ft_get(t_cmd cmd);
void						ft_mkdir(t_cmd cmd);
void						ft_send_cmd(t_cmd cmd);
void						ft_cmd_del(t_cmd **cmd);
t_cmd						*ft_get_cmd();

static t_builtin_cmd g_builtin_cmd[] = {
	{"CWD", ft_cd},
	{"PORT", ft_port},
	{"PWD", ft_pwd},
	{"QUIT", ft_quit},
	{"RETR", ft_get},
	{"LIST", ft_ls},
	{"STOR", ft_put},
	{"MKD", ft_mkdir},
	{NULL, NULL}
};
#endif
