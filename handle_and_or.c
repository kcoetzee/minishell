/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlangman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 11:56:20 by vlangman          #+#    #+#             */
/*   Updated: 2017/09/28 11:56:21 by vlangman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

int get_arg_len(const char *args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**ft_split_opps(char const *args)
{
	int 	i;
	int 	j;
	char	**ret;
	int 	len;

	i = 0;
	j = 0;
	len = get_arg_len(args);
	fprintf(stderr, "LEN: %d\n", len);
	ret = (char**)e_malloc(sizeof(char*) * (len + 1));
	ret[j] = ft_strnew(1);
	while(args[i])
	{
		if (args[i] == '"')
		{
			ret[j] = ft_addchar(ret[j], args[i]);
			while (args[i] != '"' && args[i])
			{
				ret[j] = ft_addchar(ret[j], args[i]);
				i++;
			}
			ret[j] = ft_addchar(ret[j], args[i]);
			i++;
		}
		if (args[i] == '|' && args[i + 1] && args[i + 1] == '|') //found or outside of quotes
		{
			ret[j] = ft_strjoin(ret[j], "||");
			i += 2;
			j++;
			ret[j] = ft_strnew(1);
		}
		else if (args[i] == '&' && args[i + 1] && args[i + 1] == '&')//found and outside quotes
		{
			ret[j] = ft_strjoin(ret[j], "&&");
			i += 2;
			j++;
			ret[j] = ft_strnew(1);
		}
		ret[j] = ft_addchar(ret[j], args[i]);
		i++;
	}
	j++;
	ret[j] = 0;
	return(ret);
}

int		and_or_check(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while(str[i] != '"')
			{
				i++;
				if(!str[i])
					return(0);
			}
			i++;
		}
		if (str[i] == '|' && str[i + 1] && str[i + 1] == '|') //found || outside of quotes
		{
			debug("FOUND OR\n");
			return(1);
		}
		if (str[i] == '&' && str[i + 1] && str[i + 1] == '&')
		{
			debug("FOUND AND\n");
			return(1);
		}
		i++;
	}
	return (0);
}

void		run_opps_loop(char **cmds)
{
	int			i;
	int			pid;
	int 		status;
	t_command	*list;
	t_command	*prev;

	i = 0;
	prev = NULL;
	while(cmds[i])
	{
		status = 0;
		list = create_command_list(ft_strsplit(cmds[i], ' '));
		process_input_loop(list, prev, &status);
		if (ft_strcmp(list->terminator, "||") == 0)
		{
			fprintf(stderr, "EXIT STATUS FROM COMMAND = %d\n", status);
			if (status == 0)
			{
				if (cmds[i + 1])
					i++;
				else
					break ;
			}
		}
		else
		{
			if (status > 0)
			{
				if (cmds[i + 1])
					i++;
				else
					break ;
			}
		}
		i++;
	}	
}

void		handle_and_or(const char *format)
{
	int 		i;
	char		**cmds;
	t_command	*cmd;
	t_command	*prev;

	prev = NULL;
	i = 0;
	cmds = (char**)e_malloc(sizeof(char*));
	debug("SPLITTING || AND && INTO ARRAY");
	cmds = ft_split_opps(format);
	while(cmds[i])
	{
		fprintf(stderr, "ARRAY AT POS [%d] = %s\n", i, cmds[i]);
		i++;
	}
	debug("RUNNING OPPS_LOOP");
	run_opps_loop(cmds);
}