/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:37:59 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 10:03:04 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_pwd(t_cmd cmd)
{
	char	*pwd;

	cmd.cmd = "";
	pwd = ft_get_pwd();
	if (pwd)
	{
		ft_send_responce((t_cmd_rsp){257, pwd});
		printf("PWD: %s\n", pwd);
		free(pwd);
	}
	else
	{
		ft_send_responce((t_cmd_rsp)
				{500, "Failed to get the current working directory"});
	}
}
