#include "minishell.h"

static int   ft_insert_env(t_data *data, int x, int i, char **env)
{
    int len;
    int start;
    char    *key;

    len = 0;
    start = i;
    data->flg.res = data->argv[x][i];
    while (!(ft_strchr(" \"$\'<>\\`\0?", data->argv[x][i++])))
        len++;
    if (len > 0 || data->flg.res == 63)
    {
        if (data->flg.res == 63)
        {
            key = ft_itoa(data->ret);
            *env = ft_strdup(key);
        }
        else
        {
            key = ft_substr(data->argv[x], start, len);
            *env = ft_strdup(get_var(data->env, key));
        }
        free(key);
    }
    return (len);
}

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
    char    *env;
    char    *temp;
    int     dquote;
    int     squote;
    int     omit;

    insert = ft_strdup("");
    dquote = 0;
    squote = 0;
    omit = 0;
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
                    if (data->argv[x][i + 1] == 36)
                        omit = 1;
                    i++;
                    insert = ft_charjoin(insert, data->argv[x][i]);
                }
                else
                    insert = ft_charjoin(insert, data->argv[x][i]);
            }
            else if (data->argv[x][i] == 36 && !omit && !squote)
            {
                i += ft_insert_env(data, x, i + 1, &env);
                temp = insert;
                insert = ft_strjoin(temp, env);
                free(temp);
                omit = 0;
            }
            else if (((data->argv[x][i] == 34 && !squote) || (data->argv[x][i] == 39 && !dquote)) || data->argv[x][i] != 92)
                insert = ft_charjoin(insert, data->argv[x][i]);
            i++;
        }
    }
    free(data->argv[x]);
    data->argv[x] = ft_strdup(insert);
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
        ft_unpack_argv(data, x, 0);
    }
    ft_sorter(data);
}