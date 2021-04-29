#include "minishell.h"

static void ft_env_lookup(t_data *data, char **output, int *i, int *x)
{
    char    *insert;
    int     start;
    short   result;
    int     len;

    len = 0;
    result = 0;
    if (!*(output))
        *output = ft_substr(data->cmd, 0, *i);
    start = *i + 1;
    result = data->cmd[*i + 1];
    if (result == 63)
        *i += 1;
    while(!(ft_strchr(" \\$\"'$<>|", data->cmd[++*i])) && result != 63)
        len++;
    insert = ft_strdup(getenv(ft_substr(data->cmd, start, len)));
    *x += 1;
    *i -= 1;
    if (!insert)
        insert = ft_strdup("");
    if (result == 63)
        *output = ft_strjoin(*output, ft_itoa(data->ret));
    else
        *output = ft_strjoin(*output, insert);
}

static char *ft_extract_env(t_data *data, char **output, int *x)
{
    int end;
    int i;

    i = -1;
    data->insert = 0;
    while (data->cmd[++i])
    {
        ft_flagswitch(data, data->cmd[i], 0);
        if ((ft_strchr("$", data->cmd[i])) && data->quotes != 39 && !data->escape)
        {
            ft_env_lookup(data, output, &i, x);
            end = i + 1;
            data->insert = 1;
        }
    }
    if (data->insert)
        *output = ft_strjoin(*output, ft_substr(data->cmd, end, (int)ft_strlen(data->cmd) - end));
    else
    {
        *x += 1;
        return (data->cmd);
    }
    return (*output);
}

char *ft_insert_env(t_data *data, int i, int cnt)
{
    char    *output;
    int     x;

    while (data->cmd[++i])
    {
        if (ft_strchr("$", data->cmd[i]))
        {
            if (i == 0 || (cnt == 0 && i > 0 && data->cmd[i - 1] != 32 \
            && data->cmd[i - 1] != 39 && data->cmd[i - 1] != 34 \
            && data->cmd[i - 1] != 92 && data->cmd[i - 1] != 96))
                return (data->cmd);
            cnt++;    
        }
    }     
    x = 0;
    output = NULL;
    while (x < cnt)
        output = ft_extract_env(data, &output, &x);
    return (output);
}