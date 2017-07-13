/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:24:48 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 07:24:46 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

char	*get_cmd_str(t_cmd cmd)
{
	char *re;
	char **tmp;

	re = ft_strjoin(cmd.cmd, " ");
	tmp = cmd.av;
	while (tmp && *tmp)
	{
		re = ft_strjoin_free_l(re, *(tmp++));
		re = ft_strjoin_free_l(re, " ");
	}
	re = ft_strjoin_free_l(re, "\r\n");
	return (re);
}

void	ft_send_cmd(t_cmd cmd)
{
	char *data;

	data = get_cmd_str(cmd);
	if (send(g_clt_env.svr_cmd_sock, data, strlen(data), 0) < 0)
		ft_print_exit("Failed to send command to server");
	ft_strdel(&data);
}
