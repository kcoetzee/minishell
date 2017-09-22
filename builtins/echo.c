/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:31:11 by lchant            #+#    #+#             */
/*   Updated: 2017/09/18 10:31:15 by lchant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	run_builtin_echo(t_command *command, char **envp)
{
	int i;

	i = 0;
	while (command->args->next != NULL)
	{
		ft_putstr(command->args->str);
		ft_putchar(' ');
		command->args = command->args->next;
	}
	//ft_putchar('\n');
}
