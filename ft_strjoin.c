/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 11:57:17 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/11 13:08:44 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char *ft_strnew(int len);
int	ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *join;
	int s1_len;
	int s2_len;
	int i;
	int j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	s1_len = ft_strlen(s1); 
	s2_len = ft_strlen(s2);
	join = ft_strnew(s1_len + s2_len);
	if (!join)
		return (NULL);
	while (++i < s1_len)
		*(join + i) = *(s1 + i);
	while (++j < s2_len)
		*(join + i++) = *(s2 + j);
	return (join);
}
