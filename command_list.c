#include "main.h"

int	check_opp(char *str)
{
	char	**opps;
	int	i;

	i = 0;
	opps = ft_strsplit(">,<,>>,|,;,&&,||", ',');
	while (opps[i])
	{
		if (ft_strcmp(str, opps[i]) == 0)
			return(1);
		i++;
	}
	return (0);
}

char	**arg_list_to_arr(t_args *list, t_command *cmd_list)
{
	char	*args;
	char	**newstr;

	args = ft_strjoin(cmd_list->file_name, " ");
	args = ft_strjoin(args, arg_list_to_line(list));
	newstr = ft_strsplit(args, ' ');
	return(newstr);
}

char	*arg_list_to_line(t_args *list)
{
	char	*newstr;
	newstr = (char*)malloc(sizeof(char));
	
	while(list->next)
	{
		newstr = ft_strjoin(newstr, list->str);
		newstr = ft_strjoin(newstr, " ");
		list = list->next;
	}
	return(newstr);
}

void	print_list(t_command *list)
{
	int	i;

	while (list)
	{
		i = 0;
		printf("FILE_NAME: %s\n", list->file_name);
		while(list->args)
		{
			printf("ARG%d: %s\n", i, list->args->str);
			list->args = list->args->next;
		}
		printf("TERMINATOR: %s\n", list->terminator);
		printf("NEXT: %p\n", list->next);
		list = list->next;
	}
}

t_command	*add_terminator(char *terminator, t_command *list)
{
	list->terminator = ft_strdup(terminator);
	list->next = (t_command*)malloc(sizeof(t_command));
	list = list->next;
	return (list);
}

int	ft_arr_len(char	**argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void		destroy_list(t_command *list)
{
	t_command	*tempc;
	t_args		*tempa;

	while(list->next)
	{
			while(list->args->next)
			{
				// free up the other parameters 
				free(list->args->str);
				tempa = list->args->next;
				free(list->args);
				list->args = tempa;			
			}
			free(tempa);
			free(list->file_name);
			free(list->terminator);
			tempc = list->next;
			free(list);
			list = tempc;
	}
	free(tempc);
}

t_command	*create_list(char **input)
{
	int		i;
	int		len;
	t_args		*ahead;
	t_command	*list;
	t_command	*lhead;

	i = 0;
	list = (t_command*)malloc(sizeof(t_command));
	lhead = list;
	len = ft_arr_len(input);
	while (i < len)
	{
		list->file_name = ft_strdup(input[i++]);
		list->args = (t_args*)malloc(sizeof(t_args));
		ahead = list->args;
		if (i <= len)
		{
			while(input[i] && check_opp(input[i]) != 1)
			{
				list->args->str = ft_strdup(input[i]);
				list->args->next = (t_args*)malloc(sizeof(t_args));
				list->args = list->args->next;
				i++;
			}
			list->args = ahead;
			if (i >= len)
				list = add_terminator("EOF", list);
		}
		if (i < len)
			list = add_terminator(input[i], list);
		i++;
	}
	list->next = NULL;
	return (lhead);
}
