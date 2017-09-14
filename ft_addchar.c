#include "libft.h"
#include <stdio.h>

char	*ft_addchar(char *str, char c)
{
	int		i;
	char 	*result;

	i = -1;
	result = (char*)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (str == NULL)
		return (NULL);
	while(str[++i])
		result[i] = str[i];
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}
