/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_semi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:23:42 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/29 12:23:43 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_semicolon(const char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				if (line[i] == '\0')
					exit(1);
				i++;
			}
		}
		if (line[i] == ';')
			j++;
		i++;
	}
	if (j == 0)
		return (-1);
	return (j);
}

int		pos_next_semi(const char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				if (line[i] == '\0')
				{
					exit(1);
				}
				i++;
			}
		}
		if(line[i] == ';')
		{
			return(i);
		}
		i++;
	}
	return(-1);
}

int 	arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return(i);
}

char	**ft_split_semi(const char *line)
{
	int i;
	int j;
	int pos;
	char **ret;

	i = 0;
	j = 0;
	pos = 0;
	ret = (char**)e_malloc(sizeof(char*));
	while ((pos = pos_next_semi(line, i)) >= 0)
	{
		ret[j] = ft_strsub(line, i, pos - i);
		j++;
		i = pos + 1;
	}
	ret[j] = ft_strsub(line, i, ft_strlen(line));
	ret[j + 1] = NULL;
	return(ret);
}
