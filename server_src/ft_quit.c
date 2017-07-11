/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:38:38 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 10:38:45 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_quit(t_cmd cmd)
{
	cmd.cmd = "QUIT";
	ft_send_responce((t_cmd_rsp){221, "Closing command connection"});
	printf("Closing Connection\n");
	close(g_svr_env.cln_cmd);
	exit(0);
}
