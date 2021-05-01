#include "minishell.h"

void ft_finalize(t_data *data, char **output, char **temp, int x)
{
    *temp = ft_substr(data->argv[x], data->flg.begin, data->flg.length);
    printf("temp: %s\n", *temp);
    printf("output pre finale: %s\n", *output);
    if (ft_strlen(*output) != 0)
    {
        free(data->argv[x]);
        data->argv[x] = ft_strjoin(*output, *temp);
        printf("output: %s\n", *output);
        *output = NULL;
        free(*output); 
    }
    else
    {
        free(data->argv[x]);
        printf("temp final: %s\n", *temp);
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
    char    *key;
    int     start;
    int     len;

    len = 0;
    *i += 1;
    start = *i;
    key = NULL;
    while (data->argv[x][*i] != 32 && data->argv[x][*i] != 34 \
        && data->argv[x][*i] != 36 && data->argv[x][*i] != 39 \
        && data->argv[x][*i] != 60 && data->argv[x][*i] != 62 \
        && data->argv[x][*i] != 92 && data->argv[x][*i] != 96
        && data->argv[x][*i] != 0)
    {
        *i += 1;
        len++;
    }
    data->flg.begin = *i;
    *i -= 1;
    key = ft_substr(data->argv[x], start, len);
    *insert = getenv(key);
    free(key);
}

void ft_set_prefix(t_data *data, int x, char **prefix)
{
    *prefix = ft_substr(data->argv[x], data->flg.begin, data->flg.length);
    printf("prefix: %s\n", *prefix);
    data->flg.length = 0;
}