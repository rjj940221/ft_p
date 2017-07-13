/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:13:48 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:37:19 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ft_p_server.h"

char	*ft_get_check(char **av, size_t *size)
{
	int			fd;
	struct stat	stat;
	char		*data;
	char 		*path;

	if ((path = ft_check_root(av[0], O_RDONLY)) == NULL)
	{
		ft_send_responce((t_cmd_rsp){501, "invalid server path"});
		return (NULL);
	}
	if ((fd = open(av[0], O_RDONLY)) == -1 || fstat(fd, &stat) == -1)
	{
		ft_send_responce((t_cmd_rsp){450, "Could not open file"});
		close(fd);
		return (NULL);
	}
	if ((data = mmap(0, (size_t)stat.st_size, PROT_READ, MAP_FILE |
					MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		ft_send_responce((t_cmd_rsp){450, "Could not get file data"});
		return (NULL);
	}
	*size = (size_t)stat.st_size;
	free(path);
	return (data);
}

void	ft_get(t_cmd cmd)
{
	char		*data;
	size_t		size;

	if ((data = ft_get_check(cmd.av, &size)) == NULL)
		return ;
	if (g_svr_env.cln_data != -1)
		ft_send_responce((t_cmd_rsp){125, "sending data"});
	else
	{
		ft_send_responce((t_cmd_rsp) {150, "sending data"});
		ft_connect_g_conn();
	}
	if (g_svr_env.cln_data != -1 && send(g_svr_env.cln_data,
				data, (size_t)size, 0) != -1)
		ft_send_responce((t_cmd_rsp) {226, "data sent"});
	else
		ft_send_responce((t_cmd_rsp)
				{426, "data send failed closing data connection"});
	close(g_svr_env.cln_data);
	g_svr_env.cln_data = -1;
	munmap(data, size);
}
