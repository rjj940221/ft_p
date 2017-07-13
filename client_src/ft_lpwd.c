/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lpwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:11:04 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:12:51 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void		ft_lpwd(char **argv)
{
	char	*data;

	if (argv[1])
		printf("\x1b[31mERROR: unknown parameter [%s]\x1b[0m\n", argv[1]);
	else
	{
		data = NULL;
		data = getcwd(data, MAXPATHLEN);
		if (data)
			printf("%s\n", data);
		else
			printf("\x1b[31mERROR: %s\x1b[0m\n", strerror(errno));
		ft_strdel(&data);
	}
}
