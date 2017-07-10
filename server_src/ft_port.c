//
// Created by rojones on 2017/07/08.
//

#include <netdb.h>
#include "ft_p_server.h"

int ft_2darrlen(void **arr)
{
	int re;
	char **tmp;

	re = 0;
	tmp = (char **) arr;
	while (*tmp++)
		re++;
	return re;
}

t_conn ft_get_conn(char *data)
{
	t_conn conn;
	char **tmp;


	conn = (t_conn) {NULL, -1};
	tmp = ft_strsplit(data, ',');
	if (ft_2darrlen((void **) tmp) != 6)
		return (conn);
	conn.ip = ft_strjoin(tmp[0], ".");
	conn.ip = ft_strjoin_free_l(conn.ip, tmp[1]);
	conn.ip = ft_strjoin_free_l(conn.ip, ".");
	conn.ip = ft_strjoin_free_l(conn.ip, tmp[2]);
	conn.ip = ft_strjoin_free_l(conn.ip, ".");
	conn.ip = ft_strjoin_free_l(conn.ip, tmp[3]);
	conn.port = ft_atoi(tmp[4]) * 256 + ft_atoi(tmp[5]);
	printf("port: %d\n", conn.port);
	return (conn);
}

void ft_port(t_cmd cmd)
{
	if (!cmd.av || !cmd.av[0])
		return (ft_send_responce((t_cmd_rsp) {501, "ip and port not specified"}));
	g_svr_env.data_conn = ft_get_conn(cmd.av[0]);
	if (g_svr_env.data_conn.ip == NULL)
		return (ft_send_responce((t_cmd_rsp) {501, "ip and port not specified correctly"}));
	return (ft_send_responce((t_cmd_rsp) {200, "Port okay"}));
}

void ft_connect_g_conn()
{
	struct sockaddr_in datacon;

	datacon.sin_family = AF_INET;
	datacon.sin_port = htons((uint16_t) g_svr_env.data_conn.port);
	if (inet_aton(g_svr_env.data_conn.ip, &datacon.sin_addr))
		puts("got network address");
	printf("ip to connect to: %s\n", inet_ntoa(datacon.sin_addr));
	if ((g_svr_env.cln_data = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		ft_print_exit("failed to create socket");
		return (ft_send_responce((t_cmd_rsp) {425, "failed to connect"}));
	}
	if (connect(g_svr_env.cln_data, (const struct sockaddr *) &datacon, sizeof(datacon)) < 0)
		return (ft_send_responce((t_cmd_rsp) {425, "failed to connect"}));

}