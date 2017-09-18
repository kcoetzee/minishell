/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:07:38 by lchant            #+#    #+#             */
/*   Updated: 2017/09/18 11:07:39 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	run_builtin_unsetenv(char **argv, char ***envp)
{
	t_env *list;

	list = ft_load_list(*envp);
	list = ft_unset_env(argv[1], list);
	*envp = list_to_arr(list);
}
