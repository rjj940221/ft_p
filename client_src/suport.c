//
// Created by rojones on 2017/07/06.
//

#include "../ft_p_client.h"

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

void error_exit(const char *str)
{
	printf("\x1b[31mERROR: %s\x1b[0m\n", str);
	exit(1);
}