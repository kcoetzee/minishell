#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int		get_next_line(const int fd, char **line);
int     launch_program(char **args, char **envp);

// builtin programs
void    run_builtin_echo(char **args, char **envp);
void    run_builtin_cd(char **args, char **envp);
void    run_builtin_setenv(char **args, char **envp);
void    run_builtin_unsetenv(char **args, char **envp);
void    run_builtin_env(char **args, char **envp);
void    run_builtin_exit(char **args, char **envp);

// printing-utility functions
void    debug(char *str);

#endif
