#include "minishell.h"

void    ft_increment(t_data *data, int *i)
{
    data->len++;
    *i += 1;
}

int    ft_delimiter(t_data *data, char c, char delimiter)
{
    ft_flagswitch(data, c, 0);
    if (c == delimiter && !data->quotes && !data->escape)
        return (1);
    return (0);
}

int    ft_validate(t_data *data, char *line)
{
    int i;
    int duplicate;

    i = 0;
    duplicate = 0;
    while (line[i])
    {
        if (((line[i] == 59 || line[i] == 124 || line[i] == 60) && line[i + 1] \
        && line[i + 1] == line[i]) || (line[i] == 62 && line[i + 2] && \
        line[i + 1] == 62 && line[i + 2] == 62))
        {
            duplicate = line[i];
            break ;
        }
        i++;
    }
    if (duplicate)
    {
        printf("bash: syntax error near unexpected token `%c%c'\n", duplicate, duplicate);
        ft_init(&data);
        return (1);
    }
    return (0);
}

void    ft_flagswitch(t_data *data, char c, int i)
{
    if ((c == 39 || c == 34) && !data->quotes && !data->escape)
        data->quotes = c;
    else if ((c == 39 || c == 34) && data->quotes == c && !data->escape)
        data->quotes = 0;
    else if (c == 92 && !data->escape && data->quotes != 39)
        data->escape = c;
    else if (c != 92 && data->escape == 92 && i == 0)
        data->escape = 0;
}

void    ft_reset_flags(t_data *data, int type, int cnt)
{
    if (type == 1)
    {
        data->quotes = 0;
        data->escape = 0;
    }
    else if (type == 2)
    {
        data->cmds->argc = 0;
        data->len = 0;
        data->cmds->rread = 0;
        data->cmds->rwrite = 0;
        data->cmds->fdnum = 0;
        data->cmds->pipes = 1;
        ft_close_fd(data, 2);
    }
    else if (type == 3)
    {
        data->cmds->pipe[cnt].argc = 0;
        data->cmds->pipe[cnt].argv = NULL;
        data->cmds->pipe[cnt].rread = 0;
        data->cmds->pipe[cnt].rwrite = 0;
        data->cmds->pipe[cnt].fd0 = 0;
        data->cmds->pipe[cnt].fd1 = 1;
        data->cmds->pipe[cnt].fdnum = 0;
    }
}