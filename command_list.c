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

void	debug_print_arr(char **arg)
{
	int i = 0;

	ft_putstr("DEBUG: print_arr\n");
	while (arg[i])
	{
		ft_putstr(arg[i]);
		ft_putstr(",");
		i++;
	}
	ft_putstr("\n===================\n");
	
}

char	**command_to_array(t_command *cmd)
{
	char 		**result;
	char  		*line;
	t_command	*itt;
	t_args		*args;

	itt = cmd;
	args = cmd->args;
	line = ft_strdup(itt->file_name);
	line = ft_addchar(line, ' ');

	while (args != NULL)
	{
		line = ft_strjoin(line, args->str);
		line = ft_addchar(line, ' ');
		args = args->next;
	}
	
	result = ft_strsplit(line, ' ');
	return (result);
}

void	print_command_list(t_command *command_list)
{
	int	i;
	t_command	*list;
	t_args		*args;

	list = command_list;
	while (list)
	{
		args = list->args;
		debug("--------------------------------------------");
		i = 0;
		printf("FILE_NAME: $%s$\n", list->file_name);
		while(args)
		{
			printf("ARG%d: $%s$\n", i, args->str);
			args = args->next;
			i++;
		}
		printf("TERMINATOR: $%s$\n", list->terminator);
		printf("NEXT: %p\n", list->next);
		list = list->next;
	}	
	debug("--------------------------------------------");
}

int	ft_arr_len(char	**argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void		destroy_command_list(t_command *list)
{

	//TODO: Rewrite this function
	return ;
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


static	t_args		*create_arg_list(char **input, t_command *cur_command, int *index)
{
	t_args	*head;
	t_args	*itt;

	if (input[*index] == 0){
		cur_command->terminator = ft_strdup("EOF");
		return (NULL);
	}
	else if (check_opp(input[*index])){
		cur_command->terminator = ft_strdup(input[(*index)++]);
		return (NULL);
	}
	
	head = (t_args*)malloc(sizeof(t_args));
	head->str = ft_strdup(input[(*index)++]);
	
	head->next = NULL;
	itt = head;

	while (input[*index] && check_opp(input[*index]) != 1)
	{
		itt->next = (t_args*)malloc(sizeof(t_args));	
		itt = itt->next;
		itt->str = ft_strdup(input[*index]);	
		itt->next = NULL;
		//itt = itt->next;
		(*index)++;
	}
	if (input[*index] != 0) // This means the loop exited because an operation was found
		cur_command->terminator = ft_strdup(input[(*index)++]);
	else
		cur_command->terminator = ft_strdup("EOF");
	return (head);
}

t_command	*create_command_list(char **input)
{
	int 		i;
	int 		len;
	t_command	*head;
	t_command	*itt;
	
	len = ft_arr_len(input);
	fprintf(stderr, "create_command_list: arr_len = %d\n", len);
	i = 0;
	if (input[i] == 0)
	{
		return (NULL);
	}
	
	head = (t_command*)malloc(sizeof(t_command));		
	head->file_name = ft_strdup(input[i++]);
	head->args = create_arg_list(input, head, &i);
	head->next = NULL;

	itt = head;
	while (input[i])
	{
		itt->next = (t_command*)malloc(sizeof(t_command));
		itt = itt->next;
		itt->file_name = ft_strdup(input[i++]);
		itt->args = create_arg_list(input, itt, &i);
		itt->next = NULL;
		//itt = itt->next;
		//i++;	
	}

	fprintf(stderr, "input: %s\n", input[i-1]); 
	print_command_list(head);
	return (head);
}

