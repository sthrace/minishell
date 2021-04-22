#include "minishell.h"

// int    ft_splittkn(t_data *data, char *arg, int x, int *start)
// {
//     int     i;
//     int     y;

//     i = 0;
//     y = 0;
//     if (ft_strlen(arg) == 0)
//         data->cmd[x].token[y].argv = ft_strdup("");
//     while (arg[i])
//     {
//         if (arg[i] == 34 && ((arg[i - 1] && arg[i - 1] != 92) || !(arg[i - 1])))
//             data->dqotes++;
//         else if (arg[i] == 39 && ((arg[i - 1] && arg[i - 1] != 92) || !(arg[i - 1])))
//             data->sqotes++;
//         if (arg[i] != ' ' && (((arg[i + 1] && arg[i + 1] == ' ') || !(arg[i + 1])) && (!(data->dqotes % 2) && !(data->sqotes % 2))))
//         {
//             data->cmd[x].token[y].argv = ft_substr(data->cmd[x].arg, *start, i - *start + 1);
//             printf("Token %d %d: %s\n", x, y, data->cmd[x].token[y].argv);
//             y++;
//             *start = i + 1;
//         }
//         i++;
//     }
//     return (0);
// }

// void    ft_tcnt(t_data *data, char *line, int i, int x)
// {
//     while (line[i] == ' ')
//         i++;
//     while (line[i])
//     {
//         if (line[i] == 34 && (line[i - 1] && line[i - 1] != 92))
//             data->dqotes++;
//         else if (line[i] == 39 && (line[i - 1] && line[i - 1] != 92))
//             data->sqotes++;
//         if (line[i] == ' ' && ((line[i + 1] && line[i + 1] != ' ') && (!(data->dqotes % 2) && !(data->sqotes % 2))))
//             data->cmd[x].tcnt++;
//         i++;
//     }
// }

// int    ft_splitcmd(t_data *data, int i, int *start, int x)
// {
//     if (data->line[i] == 34 && ((data->line[i - 1] && data->line[i - 1] != 92) || !(data->line[i - 1])))
// 		data->dqotes++;
// 	else if (data->line[i] == 39 && ((data->line[i - 1] && data->line[i - 1] != 92) || !(data->line[i - 1])))
// 		data->sqotes++;
// 	if (data->line[i] == 59 && (i == 0 || ((!(data->dqotes % 2) && !(data->sqotes % 2)) && (data->line[i - 1] && (data->line[i - 1] != 92 && data->line[i - 1] != 59)))))
//     {
//         if (i != 0)
//             data->cmd[x].arg = ft_substr(data->line, *start, i - *start);
//         else
//             data->cmd[x].arg = ft_strdup("");
//         *start = i + 1;
//         return (1);
//     }
//     if ((i == (int)ft_strlen(data->line) - 1) && (data->line[i]))
//         data->cmd[x].arg = ft_substr(data->line, *start, i - *start);
//     return (0);
// }

// void    ft_ccnt(t_data *data, char *line, int i)
// {
//     if (line[i] == 34 && (line[i - 1] && line[i - 1] != 92))
// 		data->dqotes++;
// 	else if (line[i] == 39 && (line[i - 1] && line[i - 1] != 92))
// 		data->sqotes++;
// 	if (line[i] == 59 && (i == 0 || ((!(data->dqotes % 2) && !(data->sqotes % 2)) && (line[i - 1] && (line[i - 1] != 92 && line[i - 1] != 59)))))
// 		data->ccnt++;
// }