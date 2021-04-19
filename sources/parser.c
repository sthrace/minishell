#include "minishell.h"

// static void ft_alloc_commands(t_shell *shell, int *i)
// {
//     shell->cmd_cnt = 0;
//     while (shell->line[*i] != '\0')
//     {
//         if (shell->line[*i] == ';')
//             break ;
//         if ((*i == 0 && shell->line[*i] != ' ') || 
//         (shell->line[*i] == ' ' && shell->line[*i + 1] 
//         && shell->line[*i + 1] != ' ' && shell->line[*i + 1] != ';'))
//         {
//             shell->cmd_cnt++;
//             (*i)++;
//         }
//         else
//             (*i)++;
//     }
// }

// static void ft_save_commands(t_shell *shell, int *i)
// {
//     shell->cmd = NULL;

//     while (shell->line[*i] != '\0')
//     {
//         if (shell->line[*i] == ';')
//             break ;
//         if ((*i == 0 && shell->line[*i] != ' ') || 
//         (shell->line[*i - 1] && shell->line[*i - 1] == ' ' 
//         && shell->line[*i] != ' ' && shell->line[*i] != ';'))
//         {
//             ft_lstadd_back(&cmd, )
//             (*i)++;
//         }
//         else
//             (*i)++;
//     }
// }

// static void ft_syntax_check(t_shell *shell, int i)
// {
//     while (shell->line[i])
//     {
//         if (shell->line[i] == ';' && shell->line[i + 1] == ';')
//         {
//             printf("parse error near `;;'\n");
//             // init_prompt();
//             exit (1);
//         }
//         i++;
//     }
// }

// void    ft_parser(t_data *data)
// {
//     int     i;

//     i = 0;
    // ft_syntax_check(shell, i);
    // ft_save_commands(shell, &i);
//     free(data->line);
//     data->line = NULL;
// }