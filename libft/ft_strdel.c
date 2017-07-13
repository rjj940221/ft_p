/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:17:16 by rojones           #+#    #+#             */
/*   Updated: 2016/06/13 15:37:16 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (*as)
		free(*as);
	*as = NULL;
}

void	ft_strarrdel(char ***as)
{
	char	**tmp;

	tmp = *as;
	while (tmp && *tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	if (*as)
		free(*as);
	*as = NULL;
}