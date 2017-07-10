//
// Created by rojones on 2017/07/08.
//

void ft_strreplace_char(char *str, char find, char replace)
{
	while(str &&*str)
	{
		if (*str == find)
			*str = replace;
		str++;
	}
}