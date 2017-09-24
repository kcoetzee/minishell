/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 10:14:55 by lchant            #+#    #+#             */
/*   Updated: 2017/06/22 10:15:00 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		read_to_string(int const fd, char **string)
{
	char	*buff;
	char	*tmp;
	int		value;

	if (!(buff = (char *)malloc(sizeof(*buff) * (BUFF_SIZE + 1))))
		return (-1);
	value = read(fd, buff, BUFF_SIZE);
	if (value > 0)
	{
		buff[value] = '\0';
		tmp = ft_strjoin(*string, buff);
		free(*string);
		*string = tmp;
	}
	free(buff);
	return (value);
}

int				get_next_line(int const fd, char **line)
{
	static char	*string = NULL;
	char		*chk;
	int			value;

	if ((!string && (string = (char *)malloc(sizeof(*string))) == NULL) || !line
			|| fd < 0 || BUFF_SIZE < 0)
		return (-1);
	chk = ft_strchr(string, '\n');
	while (chk == NULL)
	{
		value = read_to_string(fd, &string);
		if (value == 0)
		{
			if (ft_strlen(string) == 0)
				return (0);
			string = ft_strjoin(string, "\n");
		}
		if (value < 0)
			return (-1);
		else
			chk = ft_strchr(string, '\n');
	}
	*line = ft_strsub(string, 0, ft_strlen(string) - ft_strlen(chk));
	string = ft_strdup(chk + 1);
	return (1);
}
