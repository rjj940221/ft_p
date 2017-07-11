/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 12:48:38 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:40:23 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

char	*ft_ls_get_data(void)
{
	char		*data;
	char		*tmp;
	size_t		data_len;

	data_len = ft_receve_data(&data);
	tmp = data;
	if (!(data = malloc(data_len + 1)))
		return (NULL);
	data = memcpy(data, tmp, data_len);
	data[data_len] = '\0';
	if (tmp)
		free(tmp);
	return (data);
}

void	ft_ls_get_responce(void)
{
	t_cmd_rsp	rsp;
	char		*data;

	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code == 150 || rsp.code == 125)
	{
		if (rsp.code == 150)
			ft_data_connection();
		data = ft_ls_get_data();
		rsp = ft_get_cmd_responce();
		ft_process_rsp(rsp);
		if (rsp.code >= 200 && rsp.code < 300)
			printf("%s\n", data);
		if (rsp.code == 226)
		{
			close(g_clt_env.data_sock);
			g_clt_env.data_sock = -1;
		}
		if (data)
			free(data);
	}
}

void	ft_ls(char **argv)
{
	t_cmd		cmd;

	ft_port(8800);
	cmd.cmd = "LIST";
	cmd.av = NULL;
	argv = argv;
	ft_send_cmd(cmd);
	ft_ls_get_responce();
}
