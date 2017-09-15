/*
 * =====================================================================================
 *
 *       Filename:  remove_quotes.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2017 02:26:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "main.h"

char	*remove_quotes(char *str)
{
	int i;
	int j;
	int size;
	char *new_str;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '"')
			size++;
		i++;
	}
	new_str = (char*)malloc(sizeof(char) * (ft_strlen(str) - size));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (new_str);
}
