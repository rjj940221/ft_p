/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:28:56 by rojones           #+#    #+#             */
/*   Updated: 2017/07/11 10:29:21 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	*ft_get_pwd()
{
	char *buff;

	buff = NULL;
	buff = getcwd(buff, MAXPATHLEN);
	return (buff);
}
