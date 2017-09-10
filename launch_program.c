#include "main.h"

int     try_launch_local(char **args, char **envp)
{
    //debug("Trying to find binary in current folder");
    return (0);
}

int     try_launch_path(char **args, char **envp)
{
    //TODO: Replace path with extract from envp
    char *path[] = {"/bin/",0};
    char *full_name = ft_strjoin(path[0], args[0]);

    // Join the path with the name of the program
    //printf("Attempting to launch [%s], at %s\n", args[0], full_name);

    if ((execve(full_name, args, envp) == -1))
        printf("error forking \n");
}

int     launch_program(char **args, char **envp)
{
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        // Local
        if (try_launch_local(args, envp) == 0)
            try_launch_path(args, envp);

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
