//
// Created by Robert JONES on 2017/07/10.
//

#include "ft_p_client.h"

char *ft_receve_data()
{
	char	*data;
	char	buf[RCVBUFSIZE + 1];
	ssize_t rcv;

	data = NULL;
	if (g_clt_env.data_sock == -1)
		ft_print_exit("data socket not initilized");
	printf("data_sock get data: %d\n", g_clt_env.data_sock);
	while ((rcv = recv(g_clt_env.data_sock, buf, RCVBUFSIZE, 0)) > 0)
	{
		buf[rcv] = '\0';
		data = ft_strjoin_free_l(data, buf);
	}
	return data;
}