/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:19:55 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 16:51:34 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

int		check_port(const char *str)
{
	while (*str)
	{
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return (1);
}

void	ft_print_exit(char *str)
{
	printf("\x1b[31mERROR: %s\x1b[31m\n", str);
	if (g_clt_env.svr_cmd_sock > -1)
		close(g_clt_env.svr_cmd_sock);
	exit(1);
}

t_bool	ft_check_eol(char buf[2], unsigned char *r)
{
	if (buf[0] == '\r')
		*r = 1;
	else if (r && buf[0] == '\n')
		return (0);
	else
		*r = 0;
	return (1);
}
