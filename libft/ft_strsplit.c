/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:44:28 by lchant            #+#    #+#             */
/*   Updated: 2017/05/30 13:44:28 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count_words(char const *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			count++;
		i++;
	}
	if (str[0] != '\0')
		count++;
	return (count);
}

static char			*get_word(char const *str, char c, int *i)
{
	int		k;
	char	*s;

	k = 0;
	//s = (char *)malloc(sizeof(s) * (ft_strlen((char *)str)));
	s = ft_strnew(ft_strlen(str));
	if (!s)
		return (NULL);
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	**str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	word = count_words(s, c);
	str = (char **)malloc(sizeof(str) * (word + 2));
	if (!str)
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (j < word && s[i])
	{
		str[j] = get_word(s, c, &i);
		j++;
	}
	str[j] = NULL;
	return (str);
}

void	free_strsplit(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
	}
	free(arr);
}
