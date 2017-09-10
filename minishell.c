#include "main.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    debug(char *str)
{
    ft_putstr("--- ");
    ft_putstr(str);
    ft_putchar('\n');
}

void    ft_putstr(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}


void    process_input(char **envp, char *input)
{
    // TODO
    char **args;
    args = ft_strsplit(input, ' ');
    
    //char *args[] = {input, 0};

    if (ft_strequ(args[0], "cd"))
        run_builtin_cd(args, envp);
    else if (ft_strequ(args[0], "echo"))
        run_builtin_echo(args, envp);
    else if (ft_strequ(args[0], "setenv"))
        run_builtin_setenv(args, envp);
    else if (ft_strequ(args[0], "unsetenv"))
        run_builtin_unsetenv(args, envp);
    else if (ft_strequ(args[0], "env"))
        run_builtin_env(args, envp);
    else if (ft_strequ(args[0], "exit"))
        run_builtin_exit(args, envp);
    else
        ft_putstr("The program you are looking for does not exist.\n");
}

void    input_loop(char **argv, char **envp)
{
	char *line;
	line = NULL;
	
    ft_putstr("【ツ】>: ");
    while (get_next_line(0, &line) == 1)
	{
        if (line != NULL)
		{
			//printf("%s\n", line);
            process_input(envp, line);
            ft_putstr("【ツ】>: ");
            free(line);
		}
	}
}

void    test_builtin_echo(char **envp)
{
    char *argv[] = {"/bin/ls", ".", 0 };
    launch_program(argv, envp);
}

int		main(int argc, char **argv, char *envp[])
{
    int i = 0;
	//test_builtin_echo(envp);
    //launch_program(argv, envp);
    input_loop(argv, envp);
}
