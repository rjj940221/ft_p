//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_server.h"

void	ft_quit(t_cmd cmd)
{
	cmd.cmd = "QUIT";
	ft_send_responce((t_cmd_rsp){221, "service closing"});
	close(g_svr_env.cln_cmd);
	puts("exiting child process");
	exit(0);
}