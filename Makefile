#SETUP
NAME		= minishell
CC			= clang
CFLAGS		= -g3 -Wall -Wextra -Werror
RM			= rm -f

#FILES
FLS			= minishell.c termcap.c lexer.c validator.c parser.c \
				redirect.c execute.c builtins.c utils.c env.c \
				env_printer.c history.c signal.c cd.c parser_utils.c \
				execute_utils.c

SRCS_DIR	= sources/
HEADER		= $(SRCS_DIR)minishell.h
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		tools $(NAME)

$(NAME):	$(LIBFT) COMP $(OBJS) DONE
			@$(CC) $(CFLAGS) -ltermcap $(LIBFT) $(OBJS) -o $(NAME)

%.o:		%.c
			$(CC) -c $(CFLAGS) -o $@ $<
			printf "$(WHITE)██"

tools:
			@$(MAKE) -C $(LIBFT_DIR)

clean:		CLEAN
			@$(RM) $(OBJS)
			@$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean FCLEAN
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)

re:			fclean all

leaks:
			valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

git:
			make fclean
			git add .
			git commit -m "commit"
			git push

.PHONY:		all clean fclean re
.SILENT:

COMP:
	echo "$(CYAN) COMPILING $(NAME) $(DEFAULT)\n"
DONE:
	echo "$(GREEN)\n\n $(NAME) COMPILED $(DEFAULT)\n"
CLEAN :
	echo "\n$(YELLOW) REMOVING OBJECT FILES $(DEFAULT)"
FCLEAN :
	echo "$(RED) REMOVING EXECUTABLE AND LIBRARY $(DEFAULT)"

#EXTRA
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m