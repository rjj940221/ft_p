//
// Created by rojones on 2017/07/10.
//

#include <sys/stat.h>
#include "ft_p_server.h"

void ft_get(t_cmd cmd)
{
	int fd;
	struct stat stat;
	char *data;

	if (ft_check_root(cmd.av[0], O_RDONLY) == NULL)
		return ft_send_responce((t_cmd_rsp){501, "invalid server path"});
	printf("file [%s] in svrroot\n", cmd.av[0]);
	if ((fd = open(cmd.av[0], O_RDONLY)) == -1)
		return ft_send_responce((t_cmd_rsp){450, "Could not open file"});
	if (fstat(fd, &stat) == -1)
		return ft_send_responce((t_cmd_rsp){451, "Failed to get file size"});
	if ((data = mmap(0, (size_t) stat.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return ft_send_responce((t_cmd_rsp){450, "Could not get file data"});
	if (g_svr_env.cln_data != -1)
		ft_send_responce((t_cmd_rsp){125, "sending data"});
	else
	{
		ft_send_responce((t_cmd_rsp) {150, "sending data"});
		ft_connect_g_conn();
	}
	if (g_svr_env.cln_data != -1 && send(g_svr_env.cln_data, data, (size_t) stat.st_size, 0) != -1)
	{
		ft_send_responce((t_cmd_rsp) {226, "data sent"});
		close(g_svr_env.cln_data);
		g_svr_env.cln_data = -1;
	}
	else
	{
		ft_send_responce((t_cmd_rsp) {426, "data send failed closing data connection"});
		close(g_svr_env.cln_data);
		g_svr_env.cln_data = -1;
	}

}