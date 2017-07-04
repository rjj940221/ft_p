/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:13:08 by rojones           #+#    #+#             */
/*   Updated: 2017/06/20 08:56:14 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_newword(const char *s, unsigned int i, char del)
{
	if (i == 0 && s[i] == del)
		return (0);
	if (i == 0 && s[i] != del)
		return (1);
	if (s[i - 1] == del && s[i] != del)
		return (1);
	return (0);
}
