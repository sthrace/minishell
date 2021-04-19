#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <term.h>
// # include "termcap.h"

# include <stdio.h>	/////////////////
# include <sys/errno.h>
# include <string.h>

typedef struct s_command
{
    int     tcnt;
    char    *arg;
    char    **token;
}               t_command;


typedef struct s_data
{
    char        *line;
    int         linelen;
    int         dqotes;
    int         sqotes; 
    int         ccnt;
    t_command   *cmd;
}               t_data;

char    **g_env;

void        ft_initterm(struct termios *term);
void	    ft_termios(t_data *data, char *str, int len);

void        ft_line(t_data *data, char *str, int len);
void	    ft_count_commands(t_data *data, int i);

void        ft_ccnt(t_data *data, char *line, int i);
void        ft_markup_cmd(t_data *data, char *line, int i);
void        ft_initq(t_data *data);
int         ft_splitcmd(t_data *data, int i, int *start, int x);
void        ft_splittkn(t_data *data, int *start, int x, int y);

#endif