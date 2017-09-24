/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:31:44 by lchant            #+#    #+#             */
/*   Updated: 2017/09/24 08:27:14 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/*
** copy_env needs 8 lines short and i have commented the other functions
** that were commented still need??
** after j = 0 line 29 ft_putchar(i + '0');
** ft_putstr(") ");
** after ft_putchar line 33 printf("%c", envp[i][j]);
*/

void	debug_print_env(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			ft_putchar(envp[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		get_num_args(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	change_dir_absolute(char **argv, char **envp)
{
	int		ret;
	char	*path;
	t_env	*list;

	path = argv[1];
	list = ft_load_list(envp);
	if (argv[1] == 0)
	{
		debug("NO ARGUMENTS");
		path = ft_get_env("HOME", list);
		path = ft_strjoin("/", path);
	}
	else if (argv[1][0] == '~')
	{
		debug("TILDE");
		path = ft_get_env("HOME", list);
		path = ft_strjoin("/", path);
	}
	else if (argv[1][0] == '-')
	{
		debug("BACK");
		path = ft_get_env("PWD", list);
		path = ft_strjoin("/", path);
	}
	if ((ret = chdir(path)))
	{
		ft_putstr("Directory does not exist or insufficient permission.\n");
	}
	else if (argv[1] && argv[1][0] == '-')
	{
		ft_putstr(path);
		ft_putchar('\n');
	}
}

/*
** 	after run_builtin function debug("running run_bultin-cd");
*/

int	try_cd_path(t_command *command, char **envp)
{
	char	*path;
	char	**path_list;
	int		i;
	int		ret;
	int		found;
	t_env	*list;

	list = ft_load_list(envp);
	path = ft_get_env("PATH", list);
	if (path == NULL)
		return (0);
	path_list = ft_strsplit(path, ':');
	i = 0;
	found = 0;
	if (path != NULL)
		free(path);
	while (path_list[i] && !found)
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		path_list[i] = ft_strjoin(path_list[i], command->args->str);
		if ((ret = chdir(path_list[i])))
		{
		}
		else
		{
			found = 1;
		}
		i++;
	}
	return (found);
}

int	run_builtin_cd(t_command *command, char ***envp)
{
	char *home_path;
	char *cur_path;
	char *pwd;
	t_env *list;
	int		ret;

	list = ft_load_list(*envp);
	home_path = ft_get_env("HOME", list);	
	fflush(stdout);
	if (command->args->str == NULL)
	{
		if (home_path == NULL)
			fprintf(stderr, "HOME directory not set and no directory operatives\n");
		else 
		{
			printf("Home path: %s\n", home_path);
			if ((ret = chdir(home_path)))
				fprintf(stderr, "HOME directory not valid.");
			else
			{
				//list = ft_set_env("PWD", home_path, list);
				//*envp = list_to_arr(list);
			}
		}
	}
	else if (command->args->str[0] == '/' || command->args->str[0] == '.')
	{
		printf("Attempting path: %s\n", command->args->str);
		if ((ret = chdir(command->args->str)))
			ft_putstr("Invalid directory.\n");
	}
	else
	{
		if (try_cd_path(command, *envp) == 0)
		{
			cur_path = ft_strnew(ft_strlen(command->args->str));
			pwd = ft_strnew(255);
			pwd = getcwd(pwd, 255);
			cur_path = ft_strcpy(cur_path, command->args->str);
			pwd = ft_strjoin(pwd, "/");
			cur_path = ft_strjoin(pwd, cur_path);
			free(pwd);
			debug("Cur path: ");
			debug(cur_path);
			if ((ret = chdir(cur_path)))
				fprintf(stderr, "Invalid directory\n");

		}
	}


	return (1);
}

/*void	run_builtin_cd(char **argv, char **envp)
{
	char	*program_name;
	int		num_args;
	int		ret;
	char	*path;

	if (argv[1] == 0 || argv[1][0] == '/' ||
		argv[1][0] == '~' || argv[1][0] == '-')
	{
		debug("printing");
		change_dir_absolute(argv, envp);
		return ;
	}
	path = (char*)malloc(sizeof(char) * 255);
	path = getcwd(path, 255);
	if (argv[1][0] != '/')
		path = ft_strjoin(path, "/");
	printf("Current path: %s\n", path);
	printf("New path: %s\n", ft_strjoin(path, argv[1]));
	if (ret = chdir(ft_strjoin(path, argv[1])))
	{
		ft_putstr("Directory does not exist or insufficient permission.\n");
	}
}*/
/*
** t_env *list = ft_load_list(envp);
** list = ft_set_env("PWD", argv[1], list);
** envp = list_to_arr(list);
** num_args = get_num_args(argv);
** printf("Num args: %d\n", num_args);
** debug_print_env(envp);
*/
