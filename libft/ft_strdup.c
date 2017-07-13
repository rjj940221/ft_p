/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 16:21:05 by rojones           #+#    #+#             */
/*   Updated: 2016/07/18 09:17:45 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		str_size;
	char	*re;
	int		i;

	i = 0;
	str_size = ft_strlen(str);
	if (!(re = (char *)malloc((sizeof(char) * (str_size + 1)))))
		return (NULL);
	while (i <= str_size)
	{
		re[i] = str[i];
		i++;
	}
	return (re);
}

char	**ft_strarrdup(const char **strarr)
{
	char	**re;
	size_t	i;

	i = 0;
	while (strarr && strarr[i])
		i++;
	if (!(re = (char **)malloc((sizeof(char *) * (i + 1)))))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		re[i] = ft_strdup(strarr[i]);
		i++;
	}
	re[i] = NULL;
	return (re);
}