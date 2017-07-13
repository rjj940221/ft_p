/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:10:46 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:35:16 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	*ft_abspath(char *str)
{
	char	*pwd;
	char	*re;

	re = NULL;
	if (str)
	{
		if (str[0] == '/')
			re = ft_strjoin(g_svr_env.svrroot, str);
		else
		{
			pwd = ft_get_pwd();
			pwd = ft_strjoin_free_l(pwd, "/");
			re = ft_strjoin_free_l(pwd, str);
		}
	}
	return (re);
}
