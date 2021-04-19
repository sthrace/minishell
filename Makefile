#SETUP
NAME		= minishell
CC			= gcc
CFLAGS		= -fsanitize=address -Wall -Wextra -Werror
RM			= rm -f

#FILES
FLS			= minishell.c termcap.c lexer.c lexer_utils.c

SRCS_DIR	= sources/
HEADER		= $(SRCS_DIR)minishell.h
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		tools $(NAME)

$(NAME):	$(LIBFT) $(HEADER) $(OBJS)
			$(CC) $(CFLAGS) $(LIBFT) -ltermcap $(OBJS) -o $(NAME)
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

re:			fclean all

.PHONY:		all clean fclean re