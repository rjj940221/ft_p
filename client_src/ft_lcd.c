/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojones <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 09:11:44 by rojones           #+#    #+#             */
/*   Updated: 2017/07/13 09:11:47 by rojones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

void ft_lcd(char **argv)
{
	static char	*last = NULL;
	char		*tmp;
	int 		ch;

	tmp = ft_get_pwd();
	if(ft_strcmp(argv[1], "-") == 0 && last)
	{
		if ((ch = chdir(last)) == 0)
		{
			ft_strdel(&last);
			last = tmp;
		}
	}
	else if ((ch = chdir(argv[1])) == 0)
	{
		ft_strdel(&last);
		last = tmp;
	}
	if (ch != 0)
		ft_strdel(&tmp);
	printf("set last to [%s]\n",last);
}