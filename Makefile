#SETUP
NAME		= minishell
CC			= clang
CFLAGS		= -fsanitize=address -fno-omit-frame-pointer \
			--fsanitize=undefined -fsanitize=nullability -g3 -Wall -Wextra -Werror
CFLAGS		= -g3 -Wall -Wextra -Werror
RM			= rm -f

#FILES
FLS			= minishell.c termcap.c lexer.c parser.c parser_utils.c utils.c builtins.c execute.c

SRCS_DIR	= sources/
HEADER		= $(SRCS_DIR)minishell.h
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		tools $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -c -I./libft/ $< -o $(<:.c=.o)

$(NAME):	$(LIBFT) $(HEADER) $(OBJS)
			# $(CC) $(CFLAGS) $(LIBFT) -ltermcap $(OBJS) -o $(NAME)
			$(CC) $(CFLAGS) -o $(NAME) -ltermcap $(OBJS) $(LIBFT)
			@echo $(NAME) created!

tools:
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean
			@echo $(NAME) cleaned!

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

leaks:
			valgrind --show-leak-kinds=definite --leak-check=full ./$(NAME)

git:
			make fclean
			git add *
			git commit -m "commit"
			git push

re:			fclean all

.PHONY:		all clean fclean re