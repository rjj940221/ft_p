/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:08:24 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:46:31 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

char	**set_av(char **argv)
{
	char **av;

	if (!(av = malloc(2 * sizeof(char *))))
		return (NULL);
	av[0] = (ft_strchr(argv[1], '/')) ? ft_strdup(ft_strchr(argv[1], '/')) : ft_strdup(argv[1]);
	av[1] = NULL;
	return (av);
}

char	*ft_put_init(char **argv, size_t *len)
{
	int			fd;
	char		*data;
	struct stat	stat;

	if (!argv || !argv[1] || (fd = open(argv[1], O_RDONLY)) == -1)
		return (NULL);
	if (fstat(fd, &stat) == -1)
		return (NULL);
	if ((data = mmap(0, (size_t)stat.st_size, PROT_READ,
					MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return (NULL);
	*len = (size_t)stat.st_size;
	return (data);
}

void	ft_put(char **argv)
{
	size_t		size;
	char		*data;
	t_cmd		cmd;
	t_cmd_rsp	*rsp;

	if (!(data = ft_put_init(argv, &size)))
		return ;
	cmd.cmd = "STOR";
	cmd.av = set_av(argv);
	ft_send_cmd(cmd);
	ft_strarrdel(&cmd.av);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(*rsp);
	if (rsp->code == 150 || rsp->code == 126)
	{
		if (rsp->code == 150)
			ft_data_connection();
		send(g_clt_env.data_sock, data, size, 0);
		ft_close_data_sock();
		ft_cmd_responce_dell(&rsp);
		rsp = ft_get_cmd_responce();
		ft_process_rsp(*rsp);
	}
	ft_cmd_responce_dell(&rsp);
	munmap(data, size);
}
