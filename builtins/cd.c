/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:31:44 by lchant            #+#    #+#             */
/*   Updated: 2017/09/28 11:11:27 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
	list = ft_create_env_list(envp);
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

	list = ft_create_env_list(envp);
	path = ft_get_env("PATH", list);
	if (path == NULL)
		return (0);
	path_list = ft_strsplit(path, ':');
	i = 0;
	found = 0;
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

	list = ft_create_env_list(*envp);
	home_path = ft_get_env("HOME", list);
	if (command->args == NULL)
	{
		if (home_path == NULL)
			ft_putstr("HOME directory not set and no directory operatives\n");
		else if ((ret = chdir(home_path)))
			ft_putstr("HOME directory not valid.");
	}
	else if (command->args->str[0] == '/' || command->args->str[0] == '.')
	{
		if ((ret = chdir(command->args->str)))
			ft_putstr("Invalid directory.\n");
	}
	else if (try_cd_path(command, *envp) == 0)
	{
			cur_path = ft_strnew(ft_strlen(command->args->str));
			pwd = ft_strnew(255);
			pwd = getcwd(pwd, 255);
			cur_path = ft_strcpy(cur_path, command->args->str);
			pwd = ft_strjoin(pwd, "/");
			cur_path = ft_strjoin(pwd, cur_path);
			debug(cur_path);
			if ((ret = chdir(cur_path)))
				ft_putstr("Invalid directory\n");
	}
	return (1);
}
