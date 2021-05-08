#SETUP
NAME		= minishell
CC			= gcc
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

$(NAME):	tools writeComp $(OBJS) writeOK
			$(CC) $(CFLAGS) -o $(NAME) -ltermcap $(OBJS) $(LIBFT) 

.c.o:		$(NAME)
			$(CC) -c $(CFLAGS) -o $@ $<
			printf "$(WHITE)██"		

tools:
			@$(MAKE) -C $(LIBFT_DIR)

clean:
			@$(RM) $(OBJS)
			@$(MAKE) -C $(LIBFT_DIR) clean
			@echo "$(YELLOW)$(NAME) cleaned!$(DEFAULT)"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)
			@echo "$(RED)$(NAME) $(LIBFT) deleted!$(DEFAULT)"

re:			fclean all

#EXTRA
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m

.PHONY:		all clean fclean re