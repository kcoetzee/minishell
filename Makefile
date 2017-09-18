SRC = libft/ft_addchar.c libft/ft_bzero.c ft_load_list.c libft/ft_memset.c ft_set_env.c\
	libft/ft_strchr.c libft/ft_strcmp.c libft/ft_strdel.c libft/ft_strdup.c\
	libft/ft_strequ.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c\
	libft/ft_strnequ.c libft/ft_strnew.c libft/ft_strsplit.c libft/ft_strstr.c\
	libft/ft_strsub.c libft/ft_strtrim.c ft_unset_env.c get_env.c get_next_line.c\
	launch_program.c minishell.c remove_quotes.c libft/ft_countwords.c\
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/setenv.c\
	builtins/unsetenv.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = minishell

all: $(OBJ)
	gcc -c $(SRC)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ)
	rm -rf 
