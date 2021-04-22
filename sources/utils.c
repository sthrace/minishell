#include "minishell.h"

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
        if (duplicate == 124)
            exit (1);
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