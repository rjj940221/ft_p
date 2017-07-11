/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:17:35 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:17:37 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void	ft_pwd(char **argv)
{
	t_cmd	cmd;

	argv = NULL;
	cmd.cmd = "PWD";
	cmd.av = NULL;
	ft_send_cmd(cmd);
	g_clt_env.wait_rsp = TRUE;
}
