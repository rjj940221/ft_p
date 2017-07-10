//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_client.h"

void ft_ls(char **argv)
{
	t_cmd		cmd;
	t_cmd_rsp	rsp;
	pid_t 		pid;
	char		*data;

	ft_port(8800);
	cmd.cmd = "LIST";
	cmd.av = NULL;
	ft_send_cmd(cmd);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code == 150 || rsp.code == 125)
	{
		//if ((pid = fork()) != -1)
		//{
			//if (pid == 0)
		//	{
				data = ft_receve_data();
		//		exit(0);
		//	}
			rsp = ft_get_cmd_responce();
			close(g_clt_env.data_sock);
			g_clt_env.data_sock = -1;
			ft_process_rsp(rsp);
			if (rsp.code >= 200 && rsp.code < 300)
				printf("%s\n",data);
		//}
	}
}