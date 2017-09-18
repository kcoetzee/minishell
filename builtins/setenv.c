/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:08:11 by lchant            #+#    #+#             */
/*   Updated: 2017/09/18 11:08:13 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/*
** copy_env needs two lines less
** addBytes not unixcase for realloc function fix???
** newValue and newLen not unixcase for change_env function fix???
*/

int		get_num_lines(char **str)
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
	int i;
	int j;

	j = 0;
	i = 0;
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
	int		i;
	int		j;
	char	*newValue;
	int		newLen;

	i = 0;
	j = 0;
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

void	run_builtin_setenv(char **argv, char ***envp)
{
	char	*result;
	t_env	*list;

	list = ft_load_list(*envp);
	list = ft_set_env(argv[1], argv[2], list);
	*envp = list_to_arr(list);
}
