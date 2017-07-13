/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 12:59:03 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 12:59:38 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_mkdir(t_cmd cmd)
{
	char	*path;

	if (cmd.av[0] == NULL)
		ft_send_responce((t_cmd_rsp){501, "No path specified"});
	else
	{
		path = ft_abspath(cmd.av[0]);
		if (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
			ft_send_responce((t_cmd_rsp){250, path});
		else
			ft_send_responce((t_cmd_rsp){550, "failed to make directory"});
		ft_strdel(&path);
	}
}
