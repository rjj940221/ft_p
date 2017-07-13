/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lmkdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:13:57 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 13:20:50 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void	ft_lmkdir(char **argv)
{
	pid_t	pid;
	int		stat;

	if ((pid = fork()) != -1)
	{
		if (pid == 0)
		{
			execv("/bin/mkdir", argv);
			exit(0);
		}
		wait4(pid, &stat, 0, NULL);
	}
}
