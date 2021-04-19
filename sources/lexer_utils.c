#include "minishell.h"

// void    ft_splittkn(t_data *data, int *start, int x, int y)
// {
//     ft_initq(data);
//     printf("Arg: %s\n", data->cmd[x].arg);
//     printf("Arg: %c\n", *data->cmd[x].arg);
//     if (data->cmd[x].arg[y] == ' ' && !(data->dqotes % 2) && !(data->sqotes % 2))
//         y++;
//     {
//         printf("ArgInCycle: %c", *data->cmd[x].arg);
//         data->cmd[x].arg++;
//     }
//     x = 0;
//     y = 0;
//     *start = 0;
// }

void    ft_initq(t_data *data)
{
    data->sqotes = 0;
	data->dqotes = 0;
}

int    ft_splitcmd(t_data *data, int i, int *start, int x)
{
    if (data->line[i] == 34 && (data->line[i - 1] && data->line[i - 1] != 92))
		data->dqotes++;
	else if (data->line[i] == 39 && (data->line[i - 1] && data->line[i - 1] != 92))
		data->sqotes++;
	if (data->line[i] == 59 && (i == 0 || ((!(data->dqotes % 2) && !(data->sqotes % 2)) && (data->line[i - 1] && (data->line[i - 1] != 92 && data->line[i - 1] != 59)))))
    {
        if (i != 0)
            data->cmd[x].arg = ft_substr(data->line, *start, i - *start);
        else
            data->cmd[x].arg = ft_strdup("");
        *start = i + 1;
        return (1);
    }
    if ((i == (int)ft_strlen(data->line) - 1) && (data->line[i]))
        data->cmd[x].arg = ft_substr(data->line, *start, i - *start);
    return (0);
}

void    ft_ccnt(t_data *data, char *line, int i)
{
    if (line[i] == 34 && (line[i - 1] && line[i - 1] != 92))
		data->dqotes++;
	else if (line[i] == 39 && (line[i - 1] && line[i - 1] != 92))
		data->sqotes++;
	if (line[i] == 59 && (i == 0 || ((!(data->dqotes % 2) && !(data->sqotes % 2)) && (line[i - 1] && (line[i - 1] != 92 && line[i - 1] != 59)))))
		data->ccnt++;
}