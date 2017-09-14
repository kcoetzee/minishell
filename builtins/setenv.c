#include "../main.h"

int	get_num_lines(char **str)
{
	int i;
	i = 0;

	while (str[i])
	{
		i++;
	}
	return (i);
}

char	**copy_env(char **new_env, char **old_env)
{
	int i = 0;
	int j = 0;
	
	printf("LINE LEN: %d\n", get_num_lines(old_env));
	new_env = (char**)malloc(get_num_lines(old_env) + 1);
	if (new_env == NULL)
	{
		debug("error assignming memory");
		return (NULL);
	}
	while (old_env[i])
	{
		j = 0;
		printf("LINE MALLOC: %d\n", (int)ft_strlen(old_env[i]));
		new_env[i] = (char*)malloc(ft_strlen(old_env[i]) + 1);
		while (old_env[i][j])
		{
			new_env[i][j] = old_env[i][j];
			j++;
		}
		new_env[i][j] = '\0';
		i++;
	}
	old_env[i] = 0;
	return (new_env);
}

void	realloc_env(char **envp, int addBytes)
{
	
}

void	change_env(char *name, char *value, char **envp)
{
	int i = 0;
	int j = 0;

	char	*newValue;
	int	newLen;

	newLen = ft_strlen(value);
	realloc_env(envp, newLen);

	while (envp[i])
	{
		j = 0;
		if (ft_strstr(envp[i], name) && envp[i][0] == name[0])
		{
			printf("fukin found it.\n");
			ft_putstr(envp[i]);
			ft_putchar('\n');
		}
		i++;
	}
}

void    run_builtin_setenv(char **argv, char **envp)
{
	debug("running run_builtin_setenv");
	
	printf("============== ENV BEFORE COPY =================== \n");
	char **new_env = copy_env(new_env, envp);
	debug_print_env(new_env);
	printf("============== ENV COPY =================== \n");
	debug_print_env(new_env);
	//change_env(argv[1], argv[2], envp);
}
