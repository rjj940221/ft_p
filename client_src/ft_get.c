/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 12:47:38 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:13:19 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void	ft_get_process_rsp(int fd, char *fname, t_cmd_rsp *rsp)
{
	t_cmd_rsp	*tmp;
	size_t		data_len;
	char		*data;

	if (rsp->code == 150)
		ft_data_connection();
	data_len = ft_receve_data(&data);
	tmp = ft_get_cmd_responce();
	ft_process_rsp(*tmp);
	if (tmp->code >= 200 && tmp->code < 300)
		write(fd, data, data_len);
	else
		unlink(fname);
	if (tmp->code == 226)
	{
		close(g_clt_env.data_sock);
		g_clt_env.data_sock = -1;
	}
	ft_cmd_responce_dell(&tmp);
	ft_strdel(&data);
}

void	ft_get_data_responce(int fd, char *fname)
{
	t_cmd_rsp	*rsp;

	rsp = ft_get_cmd_responce();
	ft_process_rsp(*rsp);
	if (rsp->code == 150 || rsp->code == 125)
		ft_get_process_rsp(fd, fname, rsp);
	else
		unlink(fname);
	ft_cmd_responce_dell(&rsp);
}

void	ft_get(char **argv)
{
	t_cmd		cmd;
	char		*fname;
	int			fd;

	cmd.cmd = "RETR";
	cmd.av = &argv[1];
	if ((fname = strrchr(argv[1], '/')) == NULL)
		fname = argv[1];
	while (fname && *fname == '/')
		fname++;
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return ;
	ft_send_cmd(cmd);
	ft_get_data_responce(fd, fname);
}
