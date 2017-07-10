//
// Created by rojones on 2017/07/06.
//

#include "ft_p_client.h"

int check_port(const char *str)
{
	while (*str)
	{
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return 1;
}

void ft_print_exit(char *str)
{
	printf("\x1b[31mERROR: %s\x1b[31m\n", str);
	if (g_clt_env.svr_cmd_sock > -1)
		close(g_clt_env.svr_cmd_sock);
	exit(1);
}

char *get_cmd_str(t_cmd cmd)
{
	char *re;
	char **tmp;

	re = ft_strjoin(cmd.cmd, " ");
	tmp = cmd.av;
	while (tmp && *tmp)
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
	if (send(g_clt_env.svr_cmd_sock, data, strlen(data), 0) < 0)
		ft_print_exit("Failed to send command to server");
}

unsigned char	ft_check_eol(char buf[2], unsigned char *r)
{
	if (buf[0] == '\r')
		*r = 1;
	else if (r && buf[0] == '\n')
		return (0);
	else
		*r = 0;
	return (1);
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

t_cmd_rsp ft_get_cmd_responce()
{
	char *data;
	char buf[2];
	unsigned char read;
	unsigned char r;
	t_cmd_rsp		rsp;

	read = 1;
	r = 0;
	data = NULL;
	while (read)
	{
		if (recv(g_clt_env.svr_cmd_sock, buf, 1, 0) < 0)
		{
			if (data)
				free(data);
			ft_print_exit("Failed to receve command responce");
		}
		buf[1] = '\0';
		read = ft_check_eol(buf, &r);
		data = ft_strjoin_free_l(data, buf);
	}
	rsp = ft_parse_cmd_responce(data);
	free(data);
	return (rsp);
}