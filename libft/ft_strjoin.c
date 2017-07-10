/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 13:55:35 by rojones           #+#    #+#             */
/*   Updated: 2016/06/07 17:05:34 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*re;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(re = (char *)malloc((sizeof(char) * size))))
		return (NULL);
	i = 0;
	while (s1 && *s1 && i < size)
		re[i++] = *s1++;
	while (s2 && *s2 && i < size)
		re[i++] = *s2++;
	re[i] = '\0';
	return (re);
}

char	*ft_strjoin_free_l(char *s1, char const *s2)
{
	int		size;
	char	*re;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(re = (char *)malloc((sizeof(char) * size))))
		return (NULL);
	i = 0;
	while (s1 && *s1 && i < size)
		re[i++] = *s1++;
	while (s2 && *s2 && i < size)
		re[i++] = *s2++;
	re[i] = '\0';
	//if(s1)
	//	free(s1);
	return (re);
}

char	*ft_strjoin_free_r(char const *s1, char *s2)
{
	int		size;
	char	*re;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(re = (char *)malloc((sizeof(char) * size))))
		return (NULL);
	i = 0;
	while (s1 && *s1 && i < size)
		re[i++] = *s1++;
	while (s2 && *s2 && i < size)
		re[i++] = *s2++;
	re[i] = '\0';
	if (s2)
		free(s2);
	return (re);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		size;
	char	*re;
	int		i;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(re = (char *)malloc((sizeof(char) * size))))
		return (NULL);
	i = 0;
	while (s1 && *s1 && i < size)
		re[i++] = *s1++;
	while (s2 && *s2 && i < size)
		re[i++] = *s2++;
	re[i] = '\0';
	if (s1)
		free(s1);
	if(s2)
		free(s2);
	return (re);
}