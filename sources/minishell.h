#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <term.h>
// # include "termcap.h"

# include <stdio.h>	/////////////////
# include <sys/errno.h>
# include <string.h>

typedef struct s_token
{
    int     size;
    char    *arg;
}               t_token;


typedef struct s_command
{
    int         tcnt;
    t_token     *token;
}               t_command;

typedef struct s_shell
{
    char        *line;
    int         linelen; 
    int         ccnt;
    t_command   *cmd;
}               t_shell;

char    **g_env;

void        ft_initterm(struct termios *term);
void	    ft_termios(t_shell *shell, char *str, int len);

void        ft_line(t_shell *shell, char *str, int len);
void		ft_count_commands(t_shell *shell, int i);
void		ft_count_tokens(t_shell *shell, int i, int x);


#endif