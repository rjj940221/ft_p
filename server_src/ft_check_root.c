//
// Created by rojones on 2017/07/08.
//



#include "ft_p_server.h"

char	*ft_check_root(char *str, int flags)
{
	char *pwd;
	char *path;
	int		fd;

	pwd = ft_get_pwd();
	printf("checking path for ..[%s]\n", str);
	if (strncmp(str, "..", 2) == 0 && (strlen(pwd) <= strlen(g_svr_env.svrroot)))
	{
		printf("\x1B[31mERROR: not in server root\n\x1b[0m");
		free(pwd);
		return (NULL);
	}
	free(pwd);
	path = ft_abspath(str);
	printf("svr abs path [%s]\n", path);
	if  ((fd = open(path, flags)) != -1)
	{
		close(fd);
		puts("returning abs path from check");
		return (path);
	}
	free(path);
	return NULL;
}