//
// Created by rojones on 2017/07/08.
//

#include "ft_p_server.h"

char *ft_abspath(char *str)
{
	char *pwd;
	char *re;

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