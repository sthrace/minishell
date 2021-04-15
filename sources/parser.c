#include "minishell.h"

// static void ft_set_tokens(t_shell *shell, int i, int x, int y)
// {
//     int z;

//     while (x <= shell->cmd_cnt)
//     {
//         y = 0;
//         while (y <= shell->tkn_cnt)
//         {
//             z = 0;
//             shell->tkn_len = 0;
//             while (shell->line[i] != ';' && shell->line[i] != '\0')
//             {
//                 if (shell->line[i] == ' ')
//                     i++;
//                 else
//                 {
//                     shell->tkn_len++;
//                     i++;
//                     z++;
//                 }
//             }
//             printf("Shell->tkn_len: %d\n", shell->tkn_len);
//             i++;
//             y++;
//         }
//         x++;
//     }
// }

static void ft_alloc_tokens(t_shell *shell, int i, int x)
{
    while (x <= shell->cmd_cnt)
    {
        shell->tkn_cnt = 0;
        while (shell->line[i++] != ';' && shell->line[i++] != '\0')
        {
            if ((shell->line[i] == ' ' && (ft_isalpha(shell->line[i + 1]))) ||
            (i == 0 && ft_isalpha(shell->line[i])))
                shell->tkn_cnt++;
        }
        shell->cmd[x] = (char **)malloc(sizeof(char *) * shell->tkn_cnt + 1);
        i++;
        x++;
    }
    shell->cmd[x + 1] = NULL;
}

static void ft_alloc_commands(t_shell *shell, int i)
{
    shell->cmd_cnt = 0;
    while (shell->line[i])
    {
        if (shell->line[i] == ';')
        {
            if (shell->line[i + 1] == ';')
            {
                printf("parse error near `;;'\n");
                // init_prompt();
                exit (1);
            }
            if (i > 0)
                shell->cmd_cnt++;
        } 
        i++;
    }
    shell->cmd = (char ***)malloc(sizeof(char **) * (shell->cmd_cnt + 2));
    if (shell->cmd == NULL)
    {
        printf("%s\n", strerror(errno));
        exit (1);
    }
}

void    ft_parser(t_shell *shell)
{
    int     i;

    i = 0;
    ft_alloc_commands(shell, i);
    ft_alloc_tokens(shell, i, 0);
    // ft_set_tokens(shell, i, 0, 0);
    // while (shell->line[i])
    // {
    //     if (ft_metachar(shell->line[i]))
    //     {
    //         printf("Metachar\n");
    //         i++;
    //     }
    //     else if (ft_isalpha(shell->line[i]))
    //     {
    //         printf("Looks like a command\n");
    //         i++;
    //     }
    //     else if (ft_symbol(shell->line[i]))
    //     {
    //         printf("Symbol\n");
    //         i++;
    //     }
    //     else
    //         i++;
    // }
    free(shell->line);
    shell->line = NULL;
}