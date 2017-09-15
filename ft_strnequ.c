#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	else if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	else
		return (0);
}
