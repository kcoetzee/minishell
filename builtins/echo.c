#include "../main.h"


void    run_builtin_echo(char **argv, char **envp)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
