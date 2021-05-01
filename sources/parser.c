#include "minishell.h"

static int ft_quotes(char c, int *dquote, int *squote, int ret)
{
    if(c == 34)
    {
        if (!*(squote))
        {
            if (!(*dquote))
                *dquote = 1;
            else
                *dquote = 0;
            ret = 1;
        }
    } 
    else if(c == 39)
    {
        if (!(*dquote))
        {
            if (!(*squote))
                *squote = 1;
            else
                *squote = 0;
            ret = 1;
        }
    }
    return (ret);
}

static void ft_unpack_argv(t_data *data, int x, int i)
{
    char    *insert;
    int     dquote;
    int     squote;

    insert = ft_strdup("");
    dquote = 0;
    squote = 0;
    while (data->argv[x][i])
    {
        if (ft_quotes(data->argv[x][i], &dquote, &squote, 0))
            i++;
        else
        {
        if(data->argv[x][i] == 92)
        {
            if (squote)
                insert = ft_charjoin(insert, data->argv[x][i]);
            else if (!dquote || (dquote && (data->argv[x][i + 1] == 34 || data->argv[x][i + 1] == 36 || data->argv[x][i + 1] == 92 || data->argv[x][i + 1] == 96)))
            {
                i++;
                insert = ft_charjoin(insert, data->argv[x][i]);
            }
            else
                insert = ft_charjoin(insert, data->argv[x][i]);
        }
        else if (((data->argv[x][i] == 34 && !squote) || (data->argv[x][i] == 39 && !dquote)) || data->argv[x][i] != 92)
            insert = ft_charjoin(insert, data->argv[x][i]);
        i++;
        }
    }
    free(data->argv[x]);
    data->argv[x] = ft_strdup(insert);
}

static void ft_decrypt_env(t_data *data, int x, int i, char **output)
{
    char *temp;
    char *prefix;
    char *insert;

    prefix = NULL;
    while (data->argv[x][++i])
    {
        if (data->argv[x][i] != '$')
            data->flg.length++;
        ft_flags(data, data->argv[x][i], 1);
        if (ft_strchr("$", data->argv[x][i]) && data->flg.quotes != 39 && !data->flg.esc)
        {
            ft_set_prefix(data, x, &prefix);
            ft_substitute_env(data, x, &i, &insert);
            ft_join_all(&temp, &prefix, &insert, output);
            data->flg.swap = 1;
        }
    }
    if (data->flg.swap)
    {
        if (*output == NULL)
            *output = ft_strdup(prefix);
        ft_finalize(data, output, &temp, x);
        data->flg.swap = 0;
    }
}

void        ft_parser(t_data *data, int x)
{
    char *output;
    int i;

    output = ft_strdup("");
    data->flg.swap = 0;
    while (++x < data->argc)
    {
        i = -1;
        data->flg.begin = 0;
        data->flg.length = 0;
        ft_decrypt_env(data, x, i, &output);
        ft_unpack_argv(data, x, 0);
    }
    ft_sorter(data);
}