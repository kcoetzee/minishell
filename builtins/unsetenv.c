#include "../main.h"

void    run_builtin_unsetenv(char **argv, char ***envp)
{
	t_env *list;

	list = ft_load_list(*envp);
   	list = ft_unset_env(argv[1], list);
	*envp = list_to_arr(list);
}
