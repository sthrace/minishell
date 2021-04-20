#include "minishell.h"

void    ft_validator(t_data *data)
{
    char    *tmp;

    tmp = data->line;
    while(*tmp)
    {
        if ((*tmp == 59 && (*(tmp + 1) && *(tmp + 1) == 59)) || (*tmp == 124 && (*(tmp + 1) && *(tmp + 1) == 124)))
        {
            printf("parse error near `%c%c'\n", *tmp, *tmp);
            exit (1);
        }
        tmp++;
    }
}

void    ft_initqt(t_data *data, int type)
{
    int i;

    if (type == 0 || type == 2)
    {
        data->sqotes = 0;
        data->dqotes = 0;
    }
    i = 0;
    if (type == 1 || type == 2)
    {
        while (i < data->ccnt)
        {
            data->cmd[i].tcnt = 1;
            i++;
        }
    }
}