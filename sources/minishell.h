#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ncurses.h>
# include <term.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_command
{
    int     argc;
    char    **argv;
    int     fd_in;
    int     fd_out;
    char    *type;
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

void	ft_restoreterm(void);
void    ft_initterm(struct termios *term);
void	ft_termios(t_data *data, char *str, int len);

// lexer.c //

void    ft_line(t_data *data, char *str, int len);
void	ft_splitcmd(t_data *data, char *line, int i, int len);

// parser.c //

void    ft_parser(t_data *data);

// parser_utils.c //

char *ft_insert_env(char *line, int i, int cnt);

// utils.c //

int     ft_semicolumn(t_data *data, char c);
int     ft_validate(t_data *data, char *line);
void    ft_flagswitch(t_data *data, char c);
void    ft_init_flags(t_data *data);
void    ft_free_array(char **array);

// builtins.c //

void    ft_echo(int argc, char **argv);
void    ft_exit(t_data *data, int argc, char **argv);
void    ft_cd(int argc, char **argv);
void    ft_pwd(void);

// execute.c //

char *ft_binsearch(char **argv);
void  ft_execute(char **argv, char *file);

// signal.c //

void	ft_sig_handler(int sig);

// minishell.c //

void    ft_init(t_data **data);
void	ft_shell_prompt();

#endif