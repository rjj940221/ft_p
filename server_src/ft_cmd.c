//
// Created by Robert JONES on 2017/07/11.
//

#include "ft_p_server.h"

char *get_cmd_str(t_cmd cmd)
{
	char *re;
	char **tmp;

	re = ft_strjoin(cmd.cmd, " ");
	tmp = cmd.av;
	while (*tmp)
	{
		re = ft_strjoin_free_l(re, *(tmp++));
		re = ft_strjoin_free_l(re, " ");
	}
	re = ft_strjoin_free_l(re, "\r\n");
	return re;
}


void ft_send_cmd(t_cmd cmd)
{
	char *data;

	data = get_cmd_str(cmd);
	if (send(g_svr_env.cln_cmd, data, strlen(data), 0) < 0)
	{
		if (data)
			free(data);
		ft_print_exit("Failed to send command to server");
	}
	if (data)
		free(data);
}

t_cmd	ft_parse_cmd(char *data)
{
	t_cmd	re;
	char 	**tarr;

	tarr = ft_strsplit(data, ' ');
	re.cmd = tarr[0];
	re.av = ++tarr;

	return (re);
}

t_cmd	ft_get_cmd()
{
	char 			*data;
	t_cmd			tmp;
	char 			buf[2];
	unsigned char	read;
	unsigned char	r;

	read = 1;
	r = 0;
	data = NULL;
	while (read)
	{
		if (recv(g_svr_env.cln_cmd, buf, 1, 0) < 0)
		{
			if (data)
				free(data);
			ft_print_exit("Failed to receve command responce");
		}
		buf[1] = '\0';
		read = ft_check_eol(buf, &r);
		data = ft_strjoin_free_l(data, buf);
	}
	tmp = ft_parse_cmd(data);
	if (data)
		free(data);
	return (tmp);
}