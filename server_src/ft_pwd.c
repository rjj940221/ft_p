//
// Created by rojones on 2017/07/10.
//

#include "ft_p_server.h"

void ft_pwd(t_cmd cmd)
{
	char *pwd;

	pwd = ft_get_pwd();
	if (pwd)
	{
		ft_send_responce((t_cmd_rsp){257, pwd});
		printf("PWD: %s\n", pwd);
		free(pwd);
	}
	else
	{
		ft_send_responce((t_cmd_rsp){500, "Failed to get the current working directory"});
	}
}