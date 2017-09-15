#include "main.h"

int     try_launch_local(char **args, char **envp)
{
    //debug("Trying to find binary in current folder");
    return (0);
}

int		try_launch_absolute(char **args, char **envp)
{	
	
	if (args[0][0] != '/')
		return (0);
	
    // Join the path with the name of the program
    	if ((execve(args[0], args, envp) == -1))
	{
        	ft_putstr("Command invalid.\n");
		exit(0);	
	}
}

int     try_launch_path(char **args, char **envp)
{
    //TODO: Replace path with extract from envp
    //char *path[] = {"/bin/",0};
    char *path;
	char **path_list;
	int i;
	int found;
	t_env *list;

	list = ft_load_list(envp);
	path =  ft_get_env("PATH", list);
	path_list = ft_strsplit(path, ':');
	i = 0;
	found = 0;
	if (path != NULL)
		free(path);
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		path_list[i]  = ft_strjoin(path_list[i], args[0]);		
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

int	process_errors(char **args, char **envp)
{
	if (args[0] == 0) // no commands
		return (1);	
	// check for spaces/tabs
	if (args[0][0] == '\0')
		return (1);

	return (0);	
}

int     launch_program(char **args, char **envp)
{
    pid_t pid;
    pid_t wpid;
    int status;
    char	*prog_name;

	prog_name = ft_strtrim(args[0]);
	args[0] = prog_name;

	//printf("PRE ERROR, ARGS[0]: %s\n", args[0]);
	if (process_errors(args, envp))
		return (0);
			
    pid = fork();
    if (pid == 0)
    {
        // Child process
        // Local
        if (try_launch_local(args, envp) == 0)
		{
			if (try_launch_absolute(args, envp) == 0)
            	try_launch_path(args, envp);
		}

    } else if (pid < 0)
    {
        // Error with the forking
        printf("error forking, pid < 0\n");
    }
    else 
    {

        wpid = waitpid(pid, &status, WUNTRACED);
        while(!WIFEXITED(status) && !WIFSIGNALED(status))
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
}
