//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_client.h"

void ft_get(char **argv)
{
	t_cmd		cmd;
	t_cmd_rsp	rsp;
	char		*data;
	char		*fname;
	int			fd;
	size_t 		data_len;

	cmd.cmd = "RETR";
	cmd.av = &argv[1];
	if ((fname = strrchr(argv[1], '/')) == NULL)
		fname = argv[1];
	while (fname && *fname == '/')
		fname++;
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return;
	ft_send_cmd(cmd);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code == 150 || rsp.code == 125)
	{
		if (rsp.code == 150)
			ft_data_connection();
		data_len = ft_receve_data(&data);
		rsp = ft_get_cmd_responce();
		ft_process_rsp(rsp);
		if (rsp.code >= 200 && rsp.code < 300)
			write(fd, data, data_len);
		else
			unlink(fname);
		if (rsp.code == 226)
		{
			close(g_clt_env.data_sock);
			g_clt_env.data_sock = -1;
		}
	}
	else
		unlink(fname);
}