/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_fn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 07:07:47 by rojones           #+#    #+#             */
/*   Updated: 2017/07/12 07:13:33 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <printf.h>

int		countwords(char *str, int (*fn)(int))
{
	int		num;
	int		test;
	char	check;
	char	*tmp;

	num = 0;
	tmp = str;
	check = 1;
	if (!str)
		return (num);
	while (tmp && *tmp)
	{
		test = (*fn)(*tmp);
		if (test == 0 && check == 1)
		{
			num++;
			check = 0;
		}
		else if (test > 0)
			check = 1;
		tmp++;
	}
	return (num);
}

void	skip(char **str, int (*fn)(int))
{
	while ((*fn)(**str))
		(*str)++;
}

size_t	getwordsize(char *str, int (*fn)(int))
{
	size_t	re;

	if (str == NULL)
		return (0);
	re = 0;
	while (*str && (*fn)(*str) == 0)
	{
		str++;
		re++;
	}
	return (re);
}

char	**ft_strsplit_fn(char *str, int (*fn)(int))
{
	char	**re;
	size_t	idx;
	size_t	word_len;
	size_t	num_words;

	num_words = (size_t)countwords(str, fn);
	if (!(re = (char **)malloc(sizeof(char*) * (num_words + 1))))
		return (NULL);
	idx = 0;
	while (idx < num_words)
	{
		skip(&str, fn);
		word_len = getwordsize(str, fn);
		if (!(re[idx] = malloc(word_len + 1)))
		{
			free(re);
			return (NULL);
		}
		ft_strncpy(re[idx], str, word_len);
		re[idx][word_len] = '\0';
		str += word_len;
		idx++;
	}
	re[idx] = NULL;
	return (re);
}
