//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_server.h"

void	ft_quit(t_cmd cmd)
{
	puts("in quit cmd");
	cmd.cmd = "QUIT";
	ft_send_responce((t_cmd_rsp){221, "Closing command connection"});
	printf("Closing Connection\n");
	close(g_svr_env.cln_cmd);
	exit(0);
}