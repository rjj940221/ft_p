/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:19:12 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:47:16 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void	ft_quit(char **argv)
{
	t_cmd		cmd;
	t_cmd_rsp	*rsp;

	cmd.cmd = "QUIT";
	cmd.av = ++argv;
	ft_send_cmd(cmd);
	rsp = ft_get_cmd_responce();
	if (rsp->code >= 200 && rsp->code < 300)
	{
		if (g_clt_env.svr_cmd_sock > -1)
			close(g_clt_env.svr_cmd_sock);
		ft_close_data_sock();
		ft_cmd_responce_dell(&rsp);
		exit(0);
	}
	else
		ft_print_exit("Quit comand failed");
	ft_cmd_responce_dell(&rsp);
}
