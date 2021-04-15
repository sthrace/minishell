#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <term.h>
// # include "termcap.h"

# include <stdio.h>	/////////////////
# include <sys/errno.h>
# include <string.h>

typedef struct s_shell
{
    char    *line;
    int     linelen;
    char    ***cmd;
    int     cmd_cnt;
    int     *smcln_pos;
    int     tkn_cnt;
    int     tkn_len;
}               t_shell;

char    **g_env;

void ft_initterm(struct termios *term);
void	ft_termios(t_shell *shell, char *str, int len);

void ft_line(t_shell *shell, char *str, int len);
void    ft_parser(t_shell *shell);


#endif