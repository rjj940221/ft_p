/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:22:59 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:44:56 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_put(t_cmd cmd)
{
	char	*fname;
	int		fd;
	char	buff[RCVBUFSIZE];
	ssize_t	recv_size;

	if (!cmd.av || cmd.av[0] == NULL)
		return (ft_send_responce((t_cmd_rsp){501, "File name not specified"}));
	if ((fname = strrchr(cmd.av[0], '/')) == NULL)
		fname = cmd.av[0];
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC | O_EVTONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (ft_send_responce((t_cmd_rsp){450, "Unable to open file"}));
	if (g_svr_env.cln_data == -1)
	{
		ft_send_responce((t_cmd_rsp){150,
				"Opening data connection to receive on"});
		ft_connect_g_conn();
	}
	while ((recv_size = recv(g_svr_env.cln_data, buff, RCVBUFSIZE, 0)) > 0)
		write(fd, buff, (size_t)recv_size);
	ft_send_responce((t_cmd_rsp){226, "Received file"});
	close(g_svr_env.cln_data);
	g_svr_env.cln_data = -1;
}
