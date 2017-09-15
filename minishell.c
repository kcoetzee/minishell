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

void    process_input(char ***envp, char *input)
{
    // TODO
    char **args;
    args = ft_strsplit(input, ' ');
    
    //char *args[] = {input, 0};

    if (ft_strequ(args[0], "cd"))
        run_builtin_cd(args, *envp);
    else if (ft_strequ(args[0], "echo"))
        run_builtin_echo(args, *envp);
    else if (ft_strequ(args[0], "setenv"))
	{
        run_builtin_setenv(args, envp);
	}
    else if (ft_strequ(args[0], "unsetenv"))
        run_builtin_unsetenv(args, envp);
    else if (ft_strequ(args[0], "env"))
        run_builtin_env(args, *envp);
    else if (ft_strequ(args[0], "exit"))
        run_builtin_exit(args, *envp);
    else
	launch_program(args, *envp);
        //ft_putstr("The program you are looking for does not exist.\n");
}

void    input_loop(char **argv, char **envp)
{
	char *line;
	int i;

	i = 0;
	line = NULL;
	
    ft_putstr("【ツ】>: ");
    while (get_next_line(0, &line) == 1)
	{
 		if (line != NULL)
		{
			if (!ft_strchr(line, '\t'))
			{

        		process_input(&envp, line);
            	ft_putstr("【ツ】>: ");
            	free(line);
			}
		}
	}
}

int	test_vaughan_code(int argc, char **argv, char **envp)
{
	
		int		i;
		t_env	*list;

		i = -1;
		if (argc < 3)
			return (0);
		list = ft_load_list(envp);
		list = ft_set_env(argv[1], argv[2], list);
		//list = ft_unset_env(argv[1], list);
		
		envp = list_to_arr(list);
		/* 
		while(list->next != NULL)
		{
			printf("%d: %s\n", ++i, list->str);
			list = list->next;
		}*/
		debug_print_env(envp);	
		return(0);
}

int		main(int argc, char **argv, char *envp[])
{
	//test_vaughan_code(argc, argv, envp);	
	input_loop(argv, envp);
}
