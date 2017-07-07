//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_client.h"

void ft_quit(char **argv)
{
	t_cmd		cmd;
	t_cmd_rsp	rsp;

	cmd.cmd= "QUIT";
	cmd.av = ++argv;
	ft_send_cmd(cmd);
	ft_get_cmd_responce();
	if(rsp.code >= 200 && rsp.code < 300)
	{
		if (g_clt_env.svr_cmd_sock > -1)
			close(g_clt_env.svr_cmd_sock);
		exit(0);
	}
	else
		ft_print_exit("Quit comand failed");
}