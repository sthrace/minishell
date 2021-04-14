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
}               t_shell;

#endif