/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:30:52 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 10:36:11 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	*ft_ls_get_data()
{
	DIR *dir;
	struct dirent *dre;
	char	*data;

	if (!(dir = opendir(".")))
	{
		ft_send_responce((t_cmd_rsp) {451, "could not open directory"});
		return (NULL);
	}
	errno = 0;
	while ((dre = readdir(dir)) != NULL)
	{
		data = ft_strjoin_free_l(data, dre->d_name);
		data = ft_strjoin_free_l(data, "\n");
	}
	if (errno != 0)
		printf("\x1b[31mERROR: reading dir\n\x1b[0m");
	closedir(dir);
	return (data);
}

void ft_ls(t_cmd cmd)
{
	char	*data;

	cmd.cmd = NULL;
	if (!(data = ft_ls_get_data()))
		return ;
	if (g_svr_env.cln_data != -1)
		ft_send_responce((t_cmd_rsp){125, "sending data"});
	else
	{
		ft_send_responce((t_cmd_rsp) {150, "sending data"});
		ft_connect_g_conn();
	}
	if (g_svr_env.cln_data != -1 && send(g_svr_env.cln_data,data, ft_strlen(data), 0) != -1)
	{
		ft_send_responce((t_cmd_rsp) {226, "data sent"});
		close(g_svr_env.cln_data);
		g_svr_env.cln_data = -1;
	}
	else
	{
		ft_send_responce((t_cmd_rsp) {426, "data send failed closing data connection"});
		close(g_svr_env.cln_data);
	}
	return;
}
