#include "minishell.h"

static char *ft_extract_env(char *line, char **output, int i, int *x)
{
    int start;
    int end;
    int len;
    char *insert;

    while (line[++i])
    {
        if (ft_strchr("$", line[i]))
        {
            len = 0;
            if (!*(output))
                *output = ft_substr(line, 0, i);
            i++;
            start = i;
            while(!(ft_strchr(" $\"'$<>|", line[i])))
            {
                i++;
                len++;
                end = i;
            }
            insert = ft_strdup(getenv(ft_substr(line, start, len)));
            if (!insert)
                return (0x0);
            *output = ft_strjoin(*output, insert);
            i--;
            *x += 1;
        }
    }
    *output = ft_strjoin(*output, ft_substr(line, end, (int)ft_strlen(line) - end + 1));
    return (*output);
}

static char *ft_insert_env(char *line, int i, int cnt)
{
    char    *output;
    char    *insert;
    int     x;

    while (line[++i])
        if (ft_strchr("$", line[i]))
            cnt++;
    x = 0;
    output = NULL;
    insert = NULL;
    while (x < cnt)
        output = ft_extract_env(line, &output, -1, &x);
    return (output);
}

void    ft_parser(t_data *data)
{
    int     i;
    char    **argv;

    i = -1;
    argv = (char **)malloc(sizeof(char *) * data->command->argc + 1);
    if (argv == NULL)
        ft_init(&data);
    while (++i < data->command->argc)
    {
        data->command->type[i] = data->command->argv[i][0];
        if (data->command->type[i] != 39 && data->command->type[i] != 34)
            data->command->type[i] = 1;
        if (data->command->type[i] == 39 || data->command->type[i] == 34)
            argv[i] = ft_substr(data->command->argv[i], 1, ft_strlen(data->command->argv[i]) - 2);
        else
            argv[i] = ft_strdup(data->command->argv[i]);
        free(data->command->argv[i]);
        if ((data->command->type[i] == 1 || data->command->type[i] == 34) && ft_strchr(argv[i], '$'))
            argv[i] = ft_insert_env(argv[i], -1, 0);
        printf("ARGV: %s\n", argv[i]);
    }
}