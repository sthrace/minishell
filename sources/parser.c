#include "minishell.h"

void    ft_parser(t_shell *shell)
{
    int     i;

    i = 0;
    while (shell->line[i])
    {
        if (ft_symbol(shell->line[i]))
        {
            printf("Special character\n");
            i++;
        }
        else if (ft_isalpha(shell->line[i]))
        {
            printf("Looks like a command");
            i++;
        }
        else
            i++;
    }
    free(shell->line);
    shell->line = NULL;
}