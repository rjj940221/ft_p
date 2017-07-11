/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:52:42 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 10:53:11 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

int check_port(const char *str)
{
	while (*str)
	{
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return 1;
}

void ft_print_exit(char *str)
{
	printf("\x1b[31mERROR: %s\x1b[31m\n", str);
	if (g_svr_env.svr_id > -1)
		close(g_svr_env.svr_id);
	if (g_svr_env.cln_cmd > -1)
		close(g_svr_env.cln_cmd);
	if (g_svr_env.svrroot)
		free(g_svr_env.svrroot);
	exit(1);
}




t_bool ft_check_eol(char buf[2], unsigned char *r)
{
	if (buf[0] == '\r')
		*r = 1;
	else if (*r == 1 && buf[0] == '\n')
		return (0);
	else
		*r = 0;
	return (1);
}




