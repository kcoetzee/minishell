/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:53:51 by lchant            #+#    #+#             */
/*   Updated: 2017/09/28 10:11:18 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** debug("Trying to find binary in current folder");
*/

int		try_launch_local(char **args)
{
	return (0);
}

/*
** for second if Join the path with the name of the program
*/

int		try_launch_absolute(char **args)
{
	if (args[0][0] != '/')
		return (0);
	if ((execve(args[0], args, env_list_to_arr(g_shell.env_list)) == -1))
	{
		ft_putstr("Command invalid.\n");
		exit(0);
	}
	return (0);
}

int		try_launch_path(t_command *command)
{
	char	*path;
	char	**path_list;
	int		i;
	int		found;

	path = ft_get_env("PATH", g_shell.env_list);
	path_list = ft_strsplit(path, ':');
	i = 0;
	found = 0;
	if (path != NULL)
	{
		while (path_list[i])
		{
			path_list[i] = ft_strjoin(path_list[i], "/");
			path_list[i] = ft_strjoin(path_list[i], command->file_name);
			path_list[i] = remove_quotes(path_list[i]);
			if ((execve(path_list[i++], command_to_array(command), env_list_to_arr(g_shell.env_list)) != -1))
				found = 1;
		}
	}
	if (!found)
		ft_putstr("Command invalid.\n");
	return (0);
}

int		try_launch_builtins(t_command *command)
{
	if (ft_strequ(command->file_name, "echo"))
		return (run_builtin_echo(command));
	else if (ft_strequ(command->file_name, "cd"))
		return (run_builtin_cd(command));
	else if (ft_strequ(command->file_name, "env"))
		return (run_builtin_env(command));
	else if (ft_strequ(command->file_name, "exit"))
		run_builtin_exit();
	else if (ft_strequ(command->file_name, "setenv"))
		return (run_builtin_setenv(command));
	else if (ft_strequ(command->file_name, "unsetenv"))
		return (run_builtin_unsetenv(command));
	return (0);
}

int		launch_program(t_command *command)
{
	if (command->file_name[0] == '/')
	{
		execve(command->file_name, command_to_array(command), env_list_to_arr(g_shell.env_list));
		ft_putstr("Invalid path or filename. \n");
		exit(-1);
	}
	else if (try_launch_path(command) == 0)
	{
		execve(command->file_name, command_to_array(command), env_list_to_arr(g_shell.env_list));
		ft_putstr("Invalid path or filename. \n");
		exit(-1);
	}
	return(0);
}
