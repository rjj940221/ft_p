//
// Created by rojones on 2017/07/08.
//

#include <stdio.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/ioctl.h>
#include <netinet/in.h>
//#include <net/if.h>
//#include <unistd.h>
#include <arpa/inet.h>
//#include <ifaddrs.h>
//#include <wait.h>
#include "ft_p_client.h"

int ft_ip4(int port)
{
	int sock;
	struct protoent *proto;
	struct sockaddr_in sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	//sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons((uint16_t) port);
	if (bind(sock, (const struct sockaddr *) &sin, sizeof(sin)) < 0)
		ft_print_exit("Connect error");
	return (sock);
}

char *ft_get_addr_str(int sock_id)
{
	char *re;
	struct sockaddr_in sin;
	uint len;

	len = sizeof(sin);
	getsockname(sock_id, (struct sockaddr *) &sin, &len);
	re = ft_strdup(inet_ntoa(sin.sin_addr));
	ft_strreplace_char(re, '.', ',');
	re = ft_strjoin_free_l(re, ",");
	re = ft_strjoin_free(re, ft_itoa(sin.sin_port >> 0 & 0xff));
	re = ft_strjoin_free_l(re, ",");
	re = ft_strjoin_free(re, ft_itoa(sin.sin_port >> 8 & 0xff));
	return (re);
}


void ft_data_connection()
{
	unsigned int conlen;
	struct sockaddr_in conin;

	conlen = sizeof(conin);
	g_clt_env.data_sock = accept(g_clt_env.data_chanle, (struct sockaddr *) &conin, &conlen);
}

void ft_port(int port)
{
	t_cmd_rsp rsp;
	t_cmd cmd;

	cmd.cmd = "PORT";
	if (g_clt_env.data_chanle == -1)
	{
		g_clt_env.data_chanle = ft_ip4(port);
		if (listen(g_clt_env.data_chanle, 10) == -1)
			ft_print_exit("could not create listen port");
	}
	cmd.av = (char *[]) {ft_get_addr_str(g_clt_env.data_chanle), NULL};
	ft_send_cmd(cmd);
	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
	if (rsp.code >= 400 && rsp.code < 600)
			ft_print_exit("failed to create data port");
}