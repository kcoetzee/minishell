/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:23:40 by lchant            #+#    #+#             */
/*   Updated: 2017/09/29 12:23:55 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	args_check(t_command *command)
{
	char	*cur_path;
	char	*pwd;

	if (command->args->str[0] == '-')
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
	else if (check_path(command) == 1)
		return (1);
	return(0);
}

int	check_path(t_command *command)
{
	char	*cur_path;
	char	*pwd;

	if (try_cd_path(command) == 0)
	{
		cur_path = ft_strnew(ft_strlen(command->args->str));
		pwd = ft_strnew(255);
		pwd = getcwd(pwd, 255);
		cur_path = ft_strcpy(cur_path, command->args->str);
		pwd = ft_strjoin(pwd, "/");
		cur_path = ft_strjoin(pwd, cur_path);
		debug(cur_path);
		if (change_dir(cur_path) == 0)
			ft_putstr("Invalid directory\n");
	}
	return (1);
}
