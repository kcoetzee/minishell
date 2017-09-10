#include "../main.h"


void    run_builtin_echo(char **argv, char **envp)
{
    //debug("running run_builtin_echo");   
    //launch_program(argv, envp);

    printf("%s\n", argv[0]);
}
