/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:06:40 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:07:23 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strreplace_char(char *str, char find, char replace)
{
	while (str && *str)
	{
		if (*str == find)
			*str = replace;
		str++;
	}
}
