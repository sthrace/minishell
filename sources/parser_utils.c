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

static char *ft_extract_env(char *line, char **output, int i, int *x)
{
    int end;

    while (line[i])
    {
        if (ft_strchr("$", line[i]))
        {
            *output = ft_env_lookup(line, output, &i, x);
            end = i + 1;
        }
        i++;
    }
    *output = ft_strjoin(*output, ft_substr(line, end, (int)ft_strlen(line) - end));
    return (*output);
}

char *ft_insert_env(char *line, int i, int cnt)
{
    char    *output;
    int     x;

    while (line[++i])
        if (ft_strchr("$", line[i]))
            cnt++;
    x = 0;
    output = NULL;
    while (x < cnt)
        output = ft_extract_env(line, &output, 0, &x);
    return (output);
}