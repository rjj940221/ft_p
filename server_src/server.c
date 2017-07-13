/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:39:03 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:00:52 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

t_svr_env g_svr_env = (t_svr_env){-1, -1, -1, NULL,
	{0, 0, 0, {0}, "qwerfrea"}, {NULL, -1}};

t_bool	ft_check_dir(char *dir)
{
	int		fd;

	if ((fd = open(dir, O_DIRECTORY)))
	{
		close(fd);
		return (TRUE);
	}
	ft_print_exit("Failed to set server root");
	return (FALSE);
}

void	ft_svr_init_connection(int port)
{
	g_svr_env.svr_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (g_svr_env.svr_id == -1)
		ft_print_exit("Failed to create socket");
	g_svr_env.sock_in.sin_family = AF_INET;
	g_svr_env.sock_in.sin_port = htons((uint16_t)port);
	g_svr_env.sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(g_svr_env.svr_id, (const struct sockaddr *)&g_svr_env.sock_in,
				sizeof(t_tcp_sock_in)) == -1)
		ft_print_exit("failed to bind socket");
	if (listen(g_svr_env.svr_id, MAX_CLIENTS) == -1)
		ft_print_exit("socket failed to create listener");
}

int		main(int ac, char **av)
{
	int port;

	if (ac == 2 && check_port(av[1]) == 1)
		port = ft_atoi(av[1]);
	else if (ac == 4 && strcmp(av[1], "-root") == 0 && ft_check_dir(av[2]) &&
			check_port(av[3]) == 1)
	{
		g_svr_env.svrroot = strdup(av[2]);
		port = ft_atoi(av[3]);
		if (chdir(av[2]) == -1)
			ft_print_exit("failed to set server root");
	}
	else
	{
		printf("please use %s [-root /serverroot] port_num "
				"\n\te.g %s -root ~/Descktop 8080\n", av[0], av[0]);
		return (0);
	}
	if (g_svr_env.svrroot == NULL)
		g_svr_env.svrroot = ft_get_pwd();
	ft_svr_init_connection(port);
	server_loop();
	close(g_svr_env.svr_id);
}
