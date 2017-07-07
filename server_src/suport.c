//
// Created by rojones on 2017/07/06.
//


#include "ft_p_server.h"

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
	if (g_svr_env.svr_id > -1)
		close(g_svr_env.svr_id);
	if (g_svr_env.cln_cmd > -1)
		close(g_svr_env.cln_cmd);
	exit(1);
}

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

char *get_responce_str(t_cmd_rsp res)
{
	char *data;

	data = ft_itoa((int)res.code);
	data = ft_strjoin_free_l(data, " ");
	data = ft_strjoin_free_l(data, res.msg);
	data = ft_strjoin_free_l(data, "\r\n");
	return (data);
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