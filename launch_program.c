/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:53:51 by lchant            #+#    #+#             */
/*   Updated: 2017/09/18 11:53:53 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** debug("Trying to find binary in current folder");
*/

int				try_launch_local(char **args, char **envp)
{
	return (0);
}

/*
** for second if Join the path with the name of the program
*/

int				try_launch_absolute(char **args, char **envp)
{
	if (args[0][0] != '/')
		return (0);
	if ((execve(args[0], args, envp) == -1))
	{
		ft_putstr("Command invalid.\n");
		exit(0);
	}
}

/*
** remove lines from below it has 30 lines
** TODO: Replace path with extract from envp
** char *path[] = {"/bin/",0};
*/

static	void	debug_path_list(char **path_list)
{
	int i;

	i = 0;
	while (path_list[i])
	{
		printf("Pathlist[%d]: %s\n", i, path_list[i]);
		i++;
	}
}

/*
** this has 31 lines needs to reduce again
*/

int				try_launch_path(char **args, char **envp)
{
	char	*path;
	char	**path_list;
	int		i;
	int		found;
	t_env	*list;

	list = ft_load_list(envp);
	path = ft_get_env("PATH", list);
	path_list = ft_strsplit(path, ':');
	debug_path_list(path_list);
	i = 0;
	found = 0;
	if (path != NULL)
		free(path);
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		path_list[i] = ft_strjoin(path_list[i], args[0]);
		path_list[i] = remove_quotes(path_list[i]);
		printf("Attempting to launch [%s], at %s\n", args[0], path_list[i]);
		if ((execve(path_list[i], args, envp) != -1))
		{
			found = 1;
		}
		i++;
	}
	if (!found)
	{
		ft_putstr("Command invalid.\n");
		exit(0);
	}
}

/*
**  first if function no commands
** 	second if check for spaces/tabs
*/

int				process_errors(char **args, char **envp)
{
	if (args[0] == 0)
		return (1);
	if (args[0][0] == '\0')
		return (1);
	return (0);
}

/*
** lines again has 30 reduce
** first if printf("PRE ERROR, ARGS[0]: %s\n", args[0]);
** inside second if Child process, Local
** inside else statement Error with the forking
*/

int				launch_program(char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*prog_name;

	prog_name = ft_strtrim(args[0]);
	args[0] = prog_name;
	if (process_errors(args, envp))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		if (try_launch_local(args, envp) == 0)
		{
			if (try_launch_absolute(args, envp) == 0)
				try_launch_path(args, envp);
		}
	}
	else if (pid < 0)
	{
		printf("error forking, pid < 0\n");
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
}
