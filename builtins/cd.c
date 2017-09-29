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

void	debug_print_env()
{
	int i;
	int j;

	i = 0;
	j = 0;
	t_env *itt;

	itt = g_shell.env_list;
	while (itt)
	{
		ft_putstr(itt->str);
		ft_putstr("\n");
		itt = itt->next;
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



int	try_cd_path(t_command *command)
{
	char	*path;
	char	**path_list;
	int		i;
	int		ret;
	int		found;
	t_env	*list;

	path = ft_get_env("PATH", g_shell.env_list);
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

int change_dir(char *path)
{
	int ret;
	char *old;
	char *pwd;
	t_env *list;

	pwd = ft_strnew(255);
	pwd = getcwd(pwd, 255);

	if ((ret = chdir(path)))
		return (0);
	else
	{
		g_shell.env_list = ft_set_env("OLDPWD", pwd, g_shell.env_list);
		ft_putstr(path);
		return (1);
	}
}

int	run_builtin_cd(t_command *command)
{
	char *home_path;
	char *cur_path;
	char *pwd;
	t_env *list;
	int		ret;

	home_path = ft_get_env("HOME", g_shell.env_list);
	if (command->args == NULL || (command->args != NULL && command->args->str[0] == '~'))
	{
		if (home_path == NULL)
			ft_putstr("HOME directory not set and no directory operatives\n");
		else if (change_dir(home_path) == 0)
			ft_putstr("HOME directory not valid.");
		else
			return (1);
	}
	else if (command->args->str[0] == '-')
	{
		cur_path = ft_get_env("OLDPWD", g_shell.env_list);
		if (change_dir(ft_get_env("OLDPWD", g_shell.env_list)) == 0)
			ft_putstr("Invalid directory.\n");
		else
			return (1);
	}
	else if (command->args->str[0] == '/' || command->args->str[0] == '.')
	{
		if (change_dir(command->args->str) == 0)
			ft_putstr("Invalid directory.\n");
		else
			return (1);
	}
	else if (try_cd_path(command) == 0)
	{
			cur_path = ft_strnew(ft_strlen(command->args->str));
			pwd = ft_strnew(255);
			pwd = getcwd(pwd, 255);
			cur_path = ft_strcpy(cur_path, command->args->str);
			pwd = ft_strjoin(pwd, "/");
			cur_path = ft_strjoin(pwd, cur_path);
			debug(cur_path);
			if (ret = change_dir(cur_path) == 0)
				ft_putstr("Invalid directory\n");
	}
	return (1);
}
