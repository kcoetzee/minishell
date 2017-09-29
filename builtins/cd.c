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

void	debug_print_env(void)
{
	int		i;
	int		j;
	t_env	*itt;

	i = 0;
	j = 0;
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

int		try_cd_path(t_command *command)
{
	char	*path;
	char	**path_list;
	int		i;
	int		ret;
	int		found;

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
		if (change_dir(path_list[i]) == 1)
		{
			found = 1;
		}
		i++;
	}
	return (found);
}

int		change_dir(char *path)
{
	int		ret;
	char	*old;
	char	*pwd;
	t_env	*list;

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

int		run_builtin_cd(t_command *command)
{
	char	*home_path;
	char	*cur_path;
	char	*pwd;
	t_env	*list;
	int		ret;

	home_path = ft_get_env("HOME", g_shell.env_list);
	if (command->args == NULL ||
	(command->args != NULL && command->args->str[0] == '~'))
	{
		if (home_path == NULL)
			ft_putstr("HOME directory not set and no directory operatives\n");
		else if (change_dir(home_path) == 0)
			ft_putstr("HOME directory not valid.");
		else
			return (1);
	}
	else if (args_check(command) == 1)
		return (1);
	return(0);
}
