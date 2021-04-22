#include "minishell.h"

// void    ft_init_tokens(t_data *data, char *line, int i, int x)
// {
//     int y;

//     y = 0;
//     i = 0;
//     data->start = 0;
//     printf("We get input: %s\n", line);
//     while (line[i])
//     {
//         while(line[i] == 32)
//             i++;
//         ft_flagswitch(data, &line[i], i);
//         if (data->flagdq == 1)
//         {
//             i++;
//             // printf("LineD[%d]: %c(%d)\n", i, line[i], line[i]);
//             while ((line[i] != 34 && line[i] != 92) && line[i] != 0)
//                 i++;
//             if (line[i] == 34 && line[i - 1] != 92)
//                 data->flagdq = 0;
//             data->cmd[x].argv[y] = ft_substr(line, data->start, i - data->start + 1);
//             printf("TokenDQ[%d]: %s\n", y, data->cmd[x].argv[y]);
//             if (line[i] == 0)
//                 break ;
//             data->start = i + 2;
//         }
//         else if (data->flagsq == 1)
//         {
//             i++;
//             printf("LineS[%d]: %c(%d)\n", i, line[i], line[i]);
//             // while (line[i] != 39 && line[i] != 0)
//             // {
//             //     printf("LineSC[%d]: %c(%d)\n", i, line[i], line[i]);
//             //     i++;
//             // }
//             // while (data->flagdq == 0 && data->flagsq == 0) && line[i] != 0)
//             // {
//                 // printf("Flag for %d (%c | %d) is: %d\n", i, line[i], line[i], ft_flagswitch(data, &line[i], i));
//                 // i++;
//             // }
//             printf("LineAFTS[%d]: %c(%d)\n", i, line[i], line[i]);
//             printf("SFlag: %d\n", data->flagsq);
//             data->cmd[x].argv[y] = ft_substr(line, data->start, i - data->start + 1);
//             printf("TokenSQ[%d]: %s\n", y, data->cmd[x].argv[y]);
//             if (line[i] == 0)
//                 break ;
//             data->start = i + 1;
//         }
//         else
//         {
//             while (line[i] == 32)
//                 i++;
//             data->start = i;
//             while (line[i] != 32 && line[i] != 0)
//                 i++;
//             data->cmd[x].argv[y] = ft_substr(line, data->start, i - data->start);
//             printf("TokenS[%d]: %s\n", y, data->cmd[x].argv[y]);
//             if (line[i] == 0)
//                 break ;
//             data->start = i + 1;
//         }
//         y++;
//         i++;
//     }
//     // }
// }

// void    ft_set_args(t_data *data, int cnt, int x)
// {
//     int     i;

//     while (++x <= cnt)
//     {
//         i = 0;
//         data->cmd[x].argc = 1;
//         printf("Input: %s\n", data->cmd[x].input);
//         if ((int)ft_strlen(data->cmd[x].input) == 0)
//             data->cmd[x].argc = 1;
//         else
//         {
//             while (data->cmd[x].input[i] == 32)
//                 i++;
//             while (data->cmd[x].input[i])
//             {
//                 printf("Char0: %c\n", data->cmd[x].input[i]);
//                 printf("flagS0: %d\n", data->flagsq);
//                 ft_flagswitch(data, data->cmd[x].input, i);
//                 // printf("Char3: %c\n", data->cmd[x].input[i]);
//                 // printf("flagS3: %d\n", data->flagsq);
//                 if (data->cmd[x].input[i] == 32 && data->flagsq == 0 && data->flagdq == 0 && data->cmd[x].input[i + 1] && data->cmd[x].input[i + 1] != 32)
//                 {
//                     printf("Condition met\n");
//                     data->cmd[x].argc += 1;
//                 }
//                 i++;
//             }
//         }
//         printf("Argc: %d\n", data->cmd[x].argc);
//         data->cmd[x].argv = (char **)malloc(sizeof(char *) * data->cmd[x].argc);
//         data->flagsq = 0;
// 	    data->flagdq = 0;
//         printf("OK3\n");
//         ft_init_tokens(data, data->cmd[x].input, -1, x);
//     }
// }

// void    ft_init_commands(t_data *data, char *line, int i, int *cnt)
// {
//     ft_flagswitch(data, line, i);
//     if (*line == 59 && data->flagsq == 0 && data->flagdq == 0)
// 	{
// 		if (i == 0)
//         {
//             data->cmd[*cnt].input = ft_strdup("");
//             *cnt += 1;
//         }
// 		else if (i > 0 && line[i - 1] != 92)
//         {
//             data->cmd[*cnt].input = ft_substr(data->line, data->start, i - data->start);
//             data->start = i + 1;
//             *cnt += 1;
//         }
        
//     }
//     else if ((i == (int)ft_strlen(data->line) - 1) && *line != 59)
//     {
//         data->cmd[*cnt].input = ft_substr(data->line, data->start, i - data->start);
//         data->start = 0;
//     }
// }

