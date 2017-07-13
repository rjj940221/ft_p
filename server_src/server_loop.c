/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:46:40 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 11:45:32 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	search_builin(t_cmd cmd)
{
	t_builtin_cmd	*tmp;

	tmp = g_builtin_cmd;
	while (tmp->cmd)
	{
		if (strcmp(cmd.cmd, tmp->cmd) == 0)
		{
			(*tmp->fnc)(cmd);
			return ;
		}
		tmp++;
	}
	printf("\x1b[mError: Command not recognised '%s'\n\x1b[0m", cmd.cmd);
}

void	chiled(void)
{
	t_cmd	*cmd;

	close(g_svr_env.svr_id);
	while (1)
	{
		cmd = ft_get_cmd();
		search_builin(*cmd);
		ft_cmd_del(&cmd);
	}
}

void	perant(pid_t pid)
{
	pid_t	perant;
	int		stat;

	perant = wait4(pid, &stat, WNOHANG, 0);
	if (perant < 0)
		ft_print_exit("Wait failed");
	close(g_svr_env.cln_cmd);
}

void	server_loop(void)
{
	pid_t			pid;
	t_tcp_sock_in	client_sock;
	int				clientsize;

	clientsize = sizeof(client_sock);
	while (1)
	{
		if ((g_svr_env.cln_cmd = accept(g_svr_env.svr_id,
						(struct sockaddr *)&client_sock,
						(socklen_t *)&clientsize)) < 0)
			printf("accept failed\n");
		else
		{
			printf("got client %s\n", inet_ntoa(client_sock.sin_addr));
			pid = fork();
			if (pid > -1)
			{
				if (pid == 0)
					chiled();
				else
					perant(pid);
			}
		}
	}
}
