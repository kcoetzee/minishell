#include "../main.h"

void debug_print_env(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		ft_putchar(i + '0');
		ft_putstr(") ");

		while(envp[i][j])
		{
			ft_putchar(envp[i][j]);
			//printf("%c", envp[i][j]);
			j++;
		}

		ft_putchar('\n');
		i++;
	}
}

int	get_num_args(char **argv)
{
	int i;
	
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void    run_builtin_cd(char **argv, char **envp)
{
	debug("running run_bultin-cd");
	char	*program_name;
	int	num_args;
	int	ret;
	char *path;

	path = (char*)malloc(sizeof(char) * 255);
	path = getcwd(path, 255);
	path = ft_strjoin(path, "/");
	printf("Current path: %s\n", path);
	printf("New path: %s\n", ft_strjoin(path, argv[1]));
	ret = chdir(ft_strjoin(path, argv[1]));	

	//t_env *list = ft_load_list(envp);
 	//list = ft_set_env("PWD", argv[1], list);
	//envp = list_to_arr(list);
	
	//num_args = get_num_args(argv);
	//printf("Num args: %d\n", num_args);
	//debug_print_env(envp);
}
