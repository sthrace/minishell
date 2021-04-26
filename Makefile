#SETUP
NAME		= minishell
CC			= clang
CFLAGS		= -g3 -Wall -Wextra -Werror

SFLAGS		= -fsanitize=address -fno-omit-frame-pointer \
			-fsanitize=undefined -fsanitize=nullability -g3 -Wall -Wextra -Werror \
			-fsanitize=array-bounds -fsanitize=pointer-overflow
RM			= rm -f

#FILES
FLS			= minishell.c termcap.c lexer.c parser.c parser_utils.c utils.c builtins.c execute.c \
		signal.c

SRCS_DIR	= sources/
HEADER		= $(SRCS_DIR)minishell.h
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		$(NAME)

$(NAME):	tools echoCM $(OBJS) echoOK
			$(CC) $(SFLAGS) -o $(NAME) -ltermcap $(OBJS) $(LIBFT)
			# @echo $(NAME) created!

%.o: %.c
			$(CC) -c $(SFLAGS) -o $@ $<
			printf "$(WHITE)██"			

tools:
			$(MAKE) -C $(LIBFT_DIR)

clean:		echoCLEAN
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean
			# @echo $(SRCS_DIR)/$(NAME) cleaned!

fclean:		clean echoFCLEAN
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

.PHONY:		all clean fclean re leaks git
.SILENT:

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m

echoCM:
	echo "$(CYAN)Project compiling$(DEFAULT)"

echoOK:
	echo "\n"
	echo "$(GREEN)Project compiled$(DEFAULT)\n"

echoCLEAN:
	echo "\n$(RED)Object files removed$(DEFAULT)\n"

echoFCLEAN :
	echo "$(RED)Executable and libraries removed$(DEFAULT)\n"