/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_root.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:12:55 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:41:47 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	*ft_check_root(char *str, int flags)
{
	char	*pwd;
	char	*path;
	int		fd;

	pwd = ft_get_pwd();
	if (strncmp(str, "..", 2) == 0 && (strlen(pwd) <=
				strlen(g_svr_env.svrroot)))
	{
		printf("\x1B[31mERROR: not in server root\n\x1b[0m");
		free(pwd);
		return (NULL);
	}
	free(pwd);
	path = ft_abspath(str);
	if ((fd = open(path, flags)) != -1)
	{
		close(fd);
		return (path);
	}
	free(path);
	return (NULL);
}
