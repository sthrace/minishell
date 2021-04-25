#include "minishell.h"

void    ft_free_array(char **array)
{
    int cnt;

    cnt = 0;
    if (!array)
        return ;
    while (array[cnt])
    {
        free(array[cnt]);
        cnt++;
    }
    free(array);
}

int    ft_semicolumn(t_data *data, char c)
{
    ft_flagswitch(data, c);
    if (c == 59 && !data->quotes && !data->screen)
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
        if ((line[i] == 59 || line[i] == 124) && line[i + 1] && line[i + 1] == line[i])
        {
            duplicate = line[i];
            break ;
        }
        i++;
    }
    if (duplicate)
    {
        printf("syntax error near unexpected token `%c%c'\n", duplicate, duplicate);
        ft_init(&data);
        return (1);
    }
    return (0);
}

void    ft_flagswitch(t_data *data, char c)
{
    if ((c == 39 || c == 34) && !data->quotes && !data->screen)
        data->quotes = c;
    else if ((c == 39 || c == 34) && data->quotes == c && !data->screen)
        data->quotes = 0;
    else if (c == 92 && !data->screen)
        data->screen = c;
    else if (c != 92 && data->screen == 92)
        data->screen = 0;
    else if ((c == 39 || c == 34) && data->screen && (data->quotes == 34 || !data->quotes))
        data->screen = 0;
    else if (c == 39 && data->quotes == c && data->screen == 92)
        data->screen = -1;
    else if (c == 39 && data->screen == -1)
        exit (1);
}

void    ft_init_flags(t_data *data)
{
    data->quotes = 0;
    data->screen = 0;
}