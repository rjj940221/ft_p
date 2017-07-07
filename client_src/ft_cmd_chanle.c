//
// Created by rojones on 2017/07/06.
//

#include "../ft_p_client.h"

char	*ft_build_data(t_cmd cmd)
{
	char	*re;
	char 	**tmp;

	re = ft_strjoin(cmd.cmd, " ");
	tmp = cmd.av;
	while (tmp)
	{
		re = ft_strjoin_free_l(re, " ");
		re = ft_strjoin_free_l(re, *(tmp++));
	}
	return re;
}

void ft_send_cmd(t_cmd cmd)
{
	char	*data;

	data = ft_build_data(cmd);
	if (send(g_clt_env.svr_sock,data,strlen(data),0) <0)
		error_exit("Failed to send data!");
}