/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_receve_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:19:25 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:48:39 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

size_t	ft_receve_data(char **data)
{
	char	*tmp;
	char	buf[RCVBUFSIZE];
	ssize_t rcv;
	size_t	rcv_total;

	*data = NULL;
	rcv_total = 0;
	if (g_clt_env.data_sock == -1)
		ft_print_exit("data socket not initilized");
	while ((rcv = recv(g_clt_env.data_sock, buf, RCVBUFSIZE, 0)) > 0)
	{
		tmp = *data;
		rcv_total += rcv;
		*data = malloc(rcv_total);
		*data = memcpy(*data, tmp, rcv_total - rcv);
		if (tmp)
			free(tmp);
		memcpy(*data + (rcv_total - rcv), buf, (size_t)rcv);
	}
	return (rcv_total);
}
