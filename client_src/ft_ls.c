//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_client.h"

void ft_ls(char **argv)
{
	t_cmd		cmd;
	char 		*tmp;
	size_t		data_len;
	t_cmd_rsp	rsp;
	char		*data;

	ft_port(8800);
	cmd.cmd = "LIST";
	cmd.av = NULL;
	ft_send_cmd(cmd);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code == 150 || rsp.code == 125)
	{
		if (rsp.code == 150)
			ft_data_connection();
		data_len = ft_receve_data(&data);
		tmp = data;
		data = malloc(data_len + 1);
		data = memcpy(data, tmp, data_len);
		data[data_len] = '\0';
		rsp = ft_get_cmd_responce();
		ft_process_rsp(rsp);
		if (rsp.code >= 200 && rsp.code < 300)
			printf("%s\n", data);
		if (rsp.code == 226)
		{
			close(g_clt_env.data_sock);
			g_clt_env.data_sock = -1;
		}
	}
}