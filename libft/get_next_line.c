/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboudouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 17:10:25 by sboudouk          #+#    #+#             */
/*   Updated: 2014/11/22 15:35:28 by sboudouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int		gnl_check_stock(char **stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(*stock, '\n')))
	{
		*tmp = '\0';
		*line = e_ft_strdup(*stock);
		free(*stock);
		*stock = e_ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}

	return (0);
}

static int		gnl_check_read(char *buffer, char **stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(buffer, '\n')))
	{
		*tmp = '\0';

		//*line = e_ft_strjoin(*stock, buffer);
		*line = e_ft_strdup(buffer);

		free(*stock);
		*stock = e_ft_strdup(tmp + 1);
		tmp = NULL;
		free(buffer);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*stock = NULL;
	char			*buffer;
	int				ret;

	if (stock)
		if (gnl_check_stock(&stock, line))
		{
			return (1);
		}
	buffer = e_ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (gnl_check_read(buffer, &stock, line))
		{
			return (1);
		}
		stock = e_ft_strjoin(stock, buffer);
	}
	free(buffer);
	buffer = NULL;
	if (ret == -1)
		return (-1);
	if (stock == NULL)
		return (0);

	*line = ft_strdup(stock);
	free(stock);
	stock = NULL;
	return (1);
}


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
/*
#include "../main.h"

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
		printf("EXITING\n");
		buff[value] = '\0';
		tmp = e_ft_strjoin(*string, buff);
		//e_free(*string);
		*string = tmp;
	}
	return (value);
}

int				get_next_line(int const fd, char **line)
{
	static char	*string = NULL;
	char		*chk;
	int			value;
	char		*temp;

	if ((!string && (string = (char *)malloc(sizeof(*string))) == NULL) || !line
			|| fd < 0 || BUFF_SIZE < 0)
	{
		return (-1);
	}
	chk = ft_strchr(string, '\n');
	while (chk == NULL)
	{
		value = read_to_string(fd, &string);
		if (value == 0)
		{
			if (ft_strlen(string) == 0)
			{
				return (0);
			}
			temp = e_ft_strjoin(string, "\n");
			//free(string);
			string = temp;
			//e_free(string);
		}
		if (value < 0)
		{
			return (-1);
		}
		else
			chk = ft_strchr(string, '\n');
	}

	*line = e_ft_strsub(string, 0, ft_strlen(string) - ft_strlen(chk));
	string = e_ft_strdup(chk + 1);

	return (1);
}
*/
