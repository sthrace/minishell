#include "minishell.h"

void ft_finalize(t_data *data, char **output, char **temp, int x)
{
    *temp = ft_substr(data->argv[x], data->flg.begin, data->flg.length);
    if (ft_strlen(*output) != 0)
    {
        free(data->argv[x]);
        data->argv[x] = ft_strjoin(*output, *temp);
        *output = NULL;
        free(*output); 
    }
    else
    {
        free(data->argv[x]);
        data->argv[x] = ft_strdup(*temp);
    }
    *temp = NULL;
    free(*temp);
}

void ft_join_all(char **temp, char **prefix, char **insert, char **output)
{
    *temp = ft_strjoin(*prefix, *insert);
    *output = ft_strjoin(*output, *temp);
}

void ft_substitute_env(t_data *data, int x, int *i, char **insert)
{
    int     start;
    int     len;
    char    *key;

    len = 0;
    start = *i + 1;
    key = NULL;
    data->flg.res = data->argv[x][*i + 1];
    if (data->flg.res == 63)
        *i += 1;
    while (!(ft_strchr(" \"$\'<>\\`\0", data->argv[x][++*i])) && data->flg.res != 63)
        len++;
    data->flg.begin = *i;
    *i -= 1;
    if (len > 0 || data->flg.res == 63)
    {
        if (data->flg.res == 63)
        {
            key = ft_itoa(data->ret);
            *insert = ft_strdup(key);
        }
        else
        {
            key = ft_substr(data->argv[x], start, len);
            *insert = ft_strdup(getenv(key));
        }
        free(key);
    }
    else
       *insert = ft_strdup("$"); 
}

void ft_set_prefix(t_data *data, int x, char **prefix)
{
    *prefix = ft_substr(data->argv[x], data->flg.begin, data->flg.length);
    data->flg.length = 0;
}