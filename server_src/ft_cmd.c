/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:35:32 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 11:35:59 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	*get_cmd_str(t_cmd cmd)
{
	char	*re;
	char	**tmp;

	re = ft_strjoin(cmd.cmd, " ");
	tmp = cmd.av;
	while (*tmp)
	{
		re = ft_strjoin_free_l(re, *(tmp++));
		re = ft_strjoin_free_l(re, " ");
	}
	re = ft_strjoin_free_l(re, "\r\n");
	return (re);
}

void	ft_send_cmd(t_cmd cmd)
{
	char	*data;

	data = get_cmd_str(cmd);
	if (send(g_svr_env.cln_cmd, data, strlen(data), 0) < 0)
	{
		if (data)
			free(data);
		ft_print_exit("Failed to send command to server");
	}
	if (data)
		free(data);
}

void	ft_cmd_del(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (cmd && *cmd)
	{
		tmp = *cmd;
		ft_strdel(&tmp->cmd);
		ft_strarrdel(&tmp->av);
		free(tmp);
		tmp = NULL;
	}
}

t_cmd	*ft_parse_cmd(char *data)
{
	t_cmd	*re;
	char	**tarr;

	if (!(re = malloc(sizeof(t_cmd))))
		return (NULL);
	tarr = ft_strsplit(data, ' ');
	re->cmd = ft_strdup(tarr[0]);
	re->av = ft_strarrdup((const char **) &tarr[1]);
	ft_strarrdel(&tarr);
	return (re);
}

t_cmd	*ft_get_cmd(void)
{
	char			*data;
	t_cmd			*tmp;
	char			buf[2];
	t_bool 			read;
	unsigned char	r;

	read = 1;
	r = 0;
	data = NULL;
	while (read)
	{
		if (recv(g_svr_env.cln_cmd, buf, 1, 0) < 0)
		{
			if (data)
				free(data);
			ft_print_exit("Failed to receve command responce");
		}
		buf[1] = '\0';
		read = ft_check_eol(buf, &r);
		data = ft_strjoin_free_l(data, buf);
	}
	tmp = ft_parse_cmd(data);
	if (data)
		free(data);
	return (tmp);
}
