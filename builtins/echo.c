/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:31:11 by lchant            #+#    #+#             */
/*   Updated: 2017/09/25 12:30:40 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	run_builtin_echo(t_command *cmd, char **envp)
{
	int i;
	t_command *command;
	
	command = cmd;
	i = 0;
	while (command->args != NULL)
	{
		ft_putstr(command->args->str);
		ft_putchar(' ');
		command->args = command->args->next;
	}
	ft_putchar('\n');
	return (1);
	//ft_putchar('\n');
}
