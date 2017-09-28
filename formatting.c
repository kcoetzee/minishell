/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 08:19:47 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/09/28 09:04:13 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		is_opp(char c)
{
	int		i;
	char	*opps;
	char	**arr;

	i = 0;
	opps = ";,>,<,|,&";
	arr = ft_strsplit(opps, ',');
	while (arr[i] && c != arr[i][0])
		i++;
	if (arr[i] && c == arr[i][0])
		return (1);
	return (0);
}

char	*remove_tabs(char *line)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = ft_strnew(sizeof(char));
	while (line[i])
	{
		if (line[i] == '\t')
		{
			newstr = ft_addchar(newstr, ' ');
			while (line[i] && line[i] == '\t')
				i++;
		}
		newstr = ft_addchar(newstr, line[i]);
		i++;
	}
	return (newstr);
}

char	*format_opp(char *line)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	while (line[i])
	{
		j = i;
		if (is_opp(line[j]) == 1)
		{
			newstr = ft_addchar(newstr, ' ');
			while (line[j] && is_opp(line[j]) == 1)
			{
				newstr = ft_addchar(newstr, line[j]);
				j++;
			}
			newstr = ft_addchar(newstr, ' ');
			i = j;
		}
		newstr = ft_addchar(newstr, line[i]);
		i++;
	}
	return (newstr);
}

char	*format_input_string(char *line)
{
	int		i;
	char	*trimmed;
	char	*newstr;

	return (line);
	i = 0;
	trimmed = ft_strnew(sizeof(char));
	trimmed = remove_tabs(line);
	trimmed = ft_strtrim(trimmed);
	trimmed = format_opp(trimmed);
	newstr = ft_strnew(sizeof(char));
	while (trimmed[i])
	{
		while (trimmed[i] != ' ' && trimmed[i])
			newstr = ft_addchar(newstr, trimmed[i++]);
		if (trimmed[i] == ' ')
		{
			newstr = ft_addchar(newstr, trimmed[i]);
			while (trimmed[i] == ' ' && trimmed[i])
				i++;
		}
	}
	return (newstr);
}
