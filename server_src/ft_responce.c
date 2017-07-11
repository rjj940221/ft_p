//
// Created by Robert JONES on 2017/07/11.
//

#include "ft_p_server.h"

char *get_responce_str(t_cmd_rsp res)
{
	char *data;

	data = ft_itoa((int)res.code);
	data = ft_strjoin_free_l(data, " ");
	data = ft_strjoin_free_l(data, res.msg);
	data = ft_strjoin_free_l(data, "\r\n");
	return (data);
}


void	ft_send_responce(t_cmd_rsp res)
{
	char *data;

	data = get_responce_str(res);
	if (send(g_svr_env.cln_cmd, data, strlen(data), 0) < 0)
	{
		if (data)
			free(data);
		ft_print_exit("Failed to send command to server");
	}
	if (data)
		free(data);
}

t_cmd_rsp ft_parse_cmd_responce(char *data)
{
	t_cmd_rsp rsp;
	char *tmp;

	rsp.code = (short) atoi(data);
	tmp = strchr(data, ' ');
	rsp.msg = (tmp) ? strdup(++tmp) : NULL;
	return (rsp);
}

t_cmd_rsp ft_get_responce()
{
	char 			*data;
	t_cmd_rsp		tmp;
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
	tmp = ft_parse_cmd_responce(data);
	if (data)
		free(data);
	return (tmp);
}