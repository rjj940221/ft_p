//
// Created by Robert JONES on 2017/07/10.
//

#include "ft_p_server.h"

void ft_ls(t_cmd cmd)
{
	DIR *dir;
	struct dirent *dre;
	char	*data;

	cmd.cmd = NULL;
	data = NULL;
	if (!(dir = opendir(".")))
	{
		ft_send_responce((t_cmd_rsp) {451, "could not open directory"});
		return;
	}
	errno = 0;
	while ((dre = readdir(dir)) != NULL)
	{
		data = ft_strjoin_free_l(data, dre->d_name);
		data = ft_strjoin_free_l(data, "\n");
	}
	if (errno != 0)
		printf("\x1b[31mERROR: reading dir\n\x1b[0m");
	if (g_svr_env.cln_data != -1)
		ft_send_responce((t_cmd_rsp){125, "sending data"});
	else
	{
		ft_send_responce((t_cmd_rsp) {150, "sending data"});
		ft_connect_g_conn();
	}
	if (g_svr_env.cln_data != -1 && send(g_svr_env.cln_data,data, ft_strlen(data), 0) != -1)
	{
		ft_send_responce((t_cmd_rsp) {226, "data sent"});
		close(g_svr_env.cln_data);
		g_svr_env.cln_data = -1;
	}
	else
	{
		ft_send_responce((t_cmd_rsp) {426, "data send failed closing data connection"});
		close(g_svr_env.cln_data);
	}
	closedir(dir);
	return;
}