/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:11:21 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 10:12:44 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

void	ft_cd(t_cmd cmd)
{
	char	*path;

	if (cmd.av[0] == NULL)
		ft_send_responce((t_cmd_rsp){501, "No path specified"});
	else
	{
		path = ft_check_root(cmd.av[0], O_DIRECTORY);
		if (path != NULL)
		{
			if (chdir(path) == -1)
			{
				printf("\x1b[31mError: could not change to %s\n\x1b[0m",
						path);
				ft_send_responce((t_cmd_rsp){500, "Action failed"});
			}
			else
				ft_send_responce((t_cmd_rsp){250, path});
			free(path);
		}
		else
			ft_send_responce((t_cmd_rsp){550,
					"path is not a directory in the server path"});
	}
}
