//
// Created by Robert JONES on 2017/07/07.
//

# include "ft_p_client.h"

void ft_cd(char **argv)
{
	t_cmd		cmd;

	cmd.cmd = "CWD";
	cmd.av = ++argv;
	ft_send_cmd(cmd);
	g_clt_env.wait_rsp = TRUE;
}