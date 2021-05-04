#SETUP
NAME		= minishell
CC			= clang
CFLAGS		= -g3 -Wall -Wextra -Werror

SFLAGS		= -fsanitize=address -fno-omit-frame-pointer \
			-fsanitize=undefined -fsanitize=nullability \
			-fsanitize=array-bounds -fsanitize=pointer-overflow \
			-Wall -Wextra -Werror
# SFLAGS		=
RM			= rm -f

#FILES
FLS			= minishell.c termcap.c lexer.c validator.c parser.c \
				redirect.c execute.c builtins.c utils.c env.c \
				env_printer.c history.c

SRCS_DIR	= sources/
HEADER		= $(SRCS_DIR)minishell.h
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		$(NAME)

$(NAME):	tools writeComp $(OBJS) writeOK
			$(CC) $(SFLAGS) -o $(NAME) -ltermcap $(OBJS) $(LIBFT)

%.o: %.c
			$(CC) -c $(SFLAGS) -o $@ $<
			printf "$(WHITE)██"		

tools:
			$(MAKE) -C $(LIBFT_DIR)

clean:		writeCL
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean writeFCL
			$(RM) $(NAME)
			$(RM) $(LIBFT)

leaks:		
			valgrind --show-leak-kinds=definite --leak-check=full ./$(NAME)

git:
			make fclean
			@git add *
			@git commit -m "commit"
			@git push

re:			fclean all

.PHONY:		all clean fclean re leaks git
.SILENT:

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m

writeComp:
	echo "$(CYAN)COMPILING...$(DEFAULT)"

writeOK:
	echo "\n"
	echo "$(GREEN)$(NAME) => PROJECT COMPILED$(DEFAULT)\n"

writeCL:
	echo "\n$(YELLOW)*.o CLEANED$(DEFAULT)\n"

writeFCL:
	echo "$(RED)ALL CLEAN$(DEFAULT)\n"