#include "minishell.h"

static char *ft_env_lookup(char *line, char **output, int *i, int *x)
{
    char    *insert;
    int     start;
    int     len;

    len = 0;
    if (!*(output))
        *output = ft_substr(line, 0, *i);
    *i += 1;
    start = *i;
    while(!(ft_strchr(" \\$\"'$<>|", line[*i])))
    {
        *i += 1;
        len++;
    }
    insert = ft_strdup(getenv(ft_substr(line, start, len)));
    *x += 1;
    *i -= 1;
    if (!insert)
        insert = ft_strdup("");
    *output = ft_strjoin(*output, insert);
    return (*output);
}

static char *ft_extract_env(t_data *data, char *line, char **output, int *x)
{
    int end;
    int i;

    i = 0;
    data->insert = 0;
    while (line[i])
    {
        ft_flagswitch(data, line[i], 0);
        if ((ft_strchr("$", line[i])) && data->quotes != 39 && !data->escape)
        {
            *output = ft_env_lookup(line, output, &i, x);
            end = i + 1;
            data->insert = 1;
        }
        i++;
    }
    if (data->insert)
        *output = ft_strjoin(*output, ft_substr(line, end, (int)ft_strlen(line) - end));
    else
    {
        *x += 1;
        return (line);
    }
    return (*output);
}

char *ft_insert_env(t_data *data, char *line, int i, int cnt)
{
    char    *output;
    int     x;

    while (line[++i])
        if (ft_strchr("$", line[i]))
            cnt++;
    x = 0;
    output = NULL;
    while (x < cnt)
        output = ft_extract_env(data, line, &output, &x);
    return (output);
}