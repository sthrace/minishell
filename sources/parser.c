#include "minishell.h"

void        ft_parser(t_data *data, int x, int i, char *prefix)
{
    char *temp;
    char *output;
    char *insert;

    output = ft_strdup("");
    while (++x < data->argc)
    {
        i = -1;
        data->flg.begin = 0;
        data->flg.length = 0;
        while (data->argv[x][++i])
        {
            if (data->argv[x][i] != '$')
                data->flg.length++;
            ft_flags(data, data->argv[x][i], 1);
            if (ft_strchr("$", data->argv[x][i]) && data->flg.quotes != 39 && !data->flg.esc)
            {
                ft_set_prefix(data, x, &prefix);
                ft_substitute_env(data, x, &i, &insert);
                ft_join_all(&temp, &prefix, &insert, &output);
            }
        }
        ft_finalize(data, &output, &temp, x);
    }
    ft_sorter(data);
}