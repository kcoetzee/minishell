/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:47:05 by lchant            #+#    #+#             */
/*   Updated: 2017/09/25 10:58:05 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

/*
** fix this struct and s_env not separated by a single space.
*/

typedef	struct	s_command t_command;
typedef	struct	s_args t_args;

struct	s_args
{
	char	*str;
	t_args	*next;
};

struct	s_command
{
	char		*file_name;
	char		*terminator;
	t_args		*args;
	t_command	*next;	
};

typedef	struct	s_env	t_env;

struct				s_env
{
	char			*str;
	struct s_env	*next;
};

/*
** vaughan environment functions
*/
t_env	*ft_unset_env(char *key, t_env *list);
t_env	*ft_load_list(char **env);
t_env	*ft_set_env(char *key, char *value, t_env *list);
int		get_next_line(const int fd, char **line);
void	launch_program(t_command *command, char ***envp);
char	*ft_addchar(char *str, char c);
char	**list_to_arr(t_env *list);
char	*ft_get_env(char *key, t_env *list);
int		pos_equal(char *str);


void	ft_free_list(t_env *list);

/*
** builtin programs
*/
int		run_builtin_echo(t_command *command, char **envp);
int		run_builtin_cd(t_command *command, char ***envp);
int		run_builtin_setenv(t_command *command, char ***envp);
int		run_builtin_unsetenv(t_command *command, char ***envp);
int		run_builtin_env(t_command *command, char **envp);
void	run_builtin_exit(void);
char	*ft_strtrim_delim(char const *s, char delim);
char	*remove_quotes(char *str);
int	try_launch_builtins(t_command *command, char ***envp);
/*
** printing-utility functions
*/
void	debug(char *str);
void	debug_print_env(char **envp);

char	*arg_list_to_line(t_args *list);
char	**arg_list_to_arr(t_args *list, t_command *cmd_list);
void	execute_command_pipe(t_command *command, int fd[], char **envp, int state);
void	execute_command(t_command *command, char **envp);


void	print_command_list(t_command *command_list);
void		destroy_command_list(t_command *list);
t_command	*create_command_list(char **input);
char	**command_to_array(t_command *cmd);
/*
**	NORMAL FUKIN UNITLS
*/

void	free_strsplit(char **arr);
#endif
