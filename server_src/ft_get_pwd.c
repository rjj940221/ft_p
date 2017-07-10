//
// Created by rojones on 2017/07/08.
//


#include "ft_p_server.h"

char *ft_get_pwd()
{
	char *buff;

	buff = NULL;
	buff = getcwd(buff, MAXPATHLEN);
	return (buff);
}