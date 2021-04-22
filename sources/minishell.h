#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <term.h>
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_command
{
    int     argc;
    char    **argv;
    int     fd_in;
    int     fd_out;
}               t_command;


typedef struct s_data
{
    char        *line;
    int         len;
    int         quotes;
    int         screen;
    char        *cmd;
    t_command   *command;
}               t_data;

// term.c //

void        ft_initterm(struct termios *term);
void	    ft_termios(t_data *data, char *str, int len);

// lexer.c //

void        ft_line(t_data *data, char *str, int len);
void		ft_splitcmd(t_data *data, char *line, int i, int len);
int         ft_semicolumn(t_data *data, char c);

// utils.c //

int         ft_validate(t_data *data, char *line);
void        ft_flagswitch(t_data *data, char c);
void        ft_init_flags(t_data *data);

// parser.c //

void 	    ft_parser(t_data *data);

// minishell.c //

void	    ft_sig_handler(int sig);
void        ft_init(t_data **data);

#endif