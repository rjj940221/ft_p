/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recponce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:49:02 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:52:48 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

t_cmd_rsp	ft_parse_cmd_responce(char *data)
{
	t_cmd_rsp	rsp;
	char		*tmp;
	size_t		str;

	rsp.code = (short)ft_atoi(data);
	tmp = strchr(data, ' ');
	rsp.msg = (tmp) ? strdup(++tmp) : NULL;
	str = strlen(rsp.msg);
	if (str > 2)
	{
		rsp.msg[str - 1] = '\0';
		rsp.msg[str - 2] = '\0';
	}
	return (rsp);
}

t_cmd_rsp	ft_get_cmd_responce(void)
{
	char			*data;
	char			buf[2];
	unsigned char	read;
	unsigned char	r;
	t_cmd_rsp		rsp;

	read = 1;
	r = 0;
	data = NULL;
	while (read)
	{
		if (recv(g_clt_env.svr_cmd_sock, buf, 1, 0) < 0)
		{
			if (data)
				free(data);
			ft_print_exit("Failed to receve command responce");
		}
		buf[1] = '\0';
		read = ft_check_eol(buf, &r);
		data = ft_strjoin_free_l(data, buf);
	}
	rsp = ft_parse_cmd_responce(data);
	free(data);
	return (rsp);
}
