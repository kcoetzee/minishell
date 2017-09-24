SRC = launch_program.c minishell.c remove_quotes.c builtins/unsetenv.c builtins/setenv.c ft_load_list.c\
	command_list.c get_env.c builtins/echo.c builtins/cd.c builtins/exit.c builtins/env.c

NAME = minishell

LIB = -Llibft -lft

FLAGS = -Wall -Wextra -Werror

all: clean
	gcc $(SRC) -o $(NAME) $(LIB) -g

clean:
	rm -rf $(NAME)
