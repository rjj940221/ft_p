//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_client.h"

void	ft_pwd(char **argv)
{
	t_cmd	cmd;

	argv = NULL;
	cmd.cmd = "PWD";
	cmd.av = NULL;
	ft_send_cmd(cmd);
	g_clt_env.wait_rsp = TRUE;
}