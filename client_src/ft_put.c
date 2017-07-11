//
// Created by rojones on 2017/07/06.
//

# include "ft_p_client.h"

char **set_av(char	**argv)
{
	char **av;

	if (! (av = malloc(2 * sizeof(char *))))
		return (NULL);
	av[0] = (ft_strchr(argv[1], '/')) ? ft_strchr(argv[1], '/') : argv[1];
	av[1] = NULL;
	return av;
}

void ft_put(char **argv)
{
	int			fd;
	char		*data;
	struct stat	stat;
	t_cmd		cmd;
	t_cmd_rsp	rsp;

	ft_port(5000);
	if (!argv || !argv[1] || (fd = open(argv[1], O_RDONLY)) == -1)
		return ;
	if (fstat(fd, &stat) == -1)
		return ;
	if ((data = mmap(0, (size_t) stat.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return ;
	cmd.cmd = "STOR";
	cmd.av = set_av(argv);
	ft_send_cmd(cmd);
	if (cmd.av)
		free(cmd.av);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code == 150 || rsp.code == 126)
	{
		if (rsp.code == 150)
			ft_data_connection();
		send(g_clt_env.data_sock, data, (size_t)stat.st_size, 0);
		close(g_clt_env.data_sock);
		g_clt_env.data_sock = -1;
	}
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
}