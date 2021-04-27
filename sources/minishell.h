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
# include <errno.h>

typedef struct s_pipe
{
    int     argc;
    char    **argv;
    int     fd0;
    int     fd1;
    short   redir_read;
    short   redir_write;
    short   redir_append;
}               t_pipe;


typedef struct s_cmd
{
    int     argc;
    char    **argv;
    short   redir_read;
    short   redir_write;
    short   redir_append;
    t_pipe  *pipe;
}               t_cmd;


typedef struct s_data
{
    char        *line;
    int         len;
    short       quotes;
    short       escape;
    int         insert;
    int         ret;
    int         start;
    char        *cmd;
    t_cmd       *cmds;    
}               t_data;

// term.c //

void	ft_restoreterm(void);
void    ft_initterm(struct termios *term);
void	ft_termios(t_data *data, char *str, int len);

// lexer.c //

void    ft_line(t_data *data, char *str, int len);
void	ft_splitcmd(t_data *data, char *line, int i, int len);

// lexer_utils.c

char		*ft_escapes(t_data *data, char *command, int i);
char		*ft_quotes(t_data *data, char *command, int i);


// parser.c //

void        ft_parser(t_data *data, char *command);
void        ft_simple(t_data *data, char *cmd, int i);

// parser_utils.c //

char *ft_insert_env(t_data *data, char *line, int i, int cnt);

// utils.c //

int     ft_semicolumn(t_data *data, char c);
int     ft_validate(t_data *data, char *line);
void    ft_flagswitch(t_data *data, char c, int i);
void    ft_init_flags(t_data *data);
void    ft_increment(t_data *data, int *i);

// builtins.c //

void    ft_echo(int argc, char **argv);
void    ft_exit(t_data *data, int argc, char **argv, int i);
void    ft_cd(int argc, char **argv);
void    ft_pwd(void);

// execute.c //

void  ft_binsearch(char **argv);

// signal.c //

void	ft_sig_handler(int sig);
void    ft_free_array(char **array);
void    ft_free_str(char *str);

// minishell.c //

void    ft_init(t_data **data);
void	ft_shell_prompt();

#endif