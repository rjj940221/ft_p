//
// Created by rojones on 2017/07/08.
//

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
	t_conn conn;
	struct sockaddr_in datacon;

	if (!cmd.av || !cmd.av[0])
		return (ft_send_responce((t_cmd_rsp) {501, "ip and port not specified"}));
	conn = ft_get_conn(cmd.av[0]);
	if (conn.ip == NULL)
		return (ft_send_responce((t_cmd_rsp) {501, "ip and port not specified correctly"}));
	datacon.sin_family = AF_INET;
	datacon.sin_port = htons((uint16_t) 8800);
	if (inet_aton(conn.ip, &datacon.sin_addr))
		puts("got network address");
	printf("ip to connect to: %s\n",inet_ntoa(datacon.sin_addr));
	if (connect(g_svr_env.cln_data, (const struct sockaddr *) &datacon, sizeof(datacon)) < 0)
		return (ft_send_responce((t_cmd_rsp) {425, "failed to connect"}));
	ft_send_responce((t_cmd_rsp) {200, "connected"});
}