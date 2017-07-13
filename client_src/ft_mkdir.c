/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:13:37 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:13:47 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void	ft_mkdir(char **argv)
{
	t_cmd	cmd;

	cmd.cmd = "MKD";
	cmd.av = ++argv;
	ft_send_cmd(cmd);
	g_clt_env.wait_rsp = TRUE;
}
