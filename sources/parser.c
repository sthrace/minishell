#include "minishell.h"

static int   ft_insert_env(t_data *data, int x, int i, char **env)
{
    char    *key;

    data->len = 0;
    data->flg.start = i;
    data->flg.res = data->argv[x][i];
    while (!(ft_strchr("= \"$\'<>\\`\0?", data->argv[x][i++])))
        data->len++;
    if (data->len > 0 || data->flg.res == 63)
    {
        if (data->flg.res == 63)
        {
            key = ft_itoa(data->ret);
            *env = ft_strdup(key);
			free(key);
			return (data->len);
        }
        key = ft_substr(data->argv[x], data->flg.start, data->len);
		if (!get_var(data->env, key))
			*env = ft_strdup("");
		else
            *env = ft_strdup(get_var(data->env, key));
        free(key);
    }
    return (data->len);
}

static int ft_quotes(t_data *data, char c, int ret)
{
    if(c == 34)
    {
        if (!data->flg.squote)
        {
            if (!data->flg.dquote)
                data->flg.dquote = 1;
            else
                data->flg.dquote = 0;
            ret = 1;
        }
    } 
    else if(c == 39)
    {
        if (!data->flg.dquote)
        {
            if (!data->flg.squote)
                data->flg.squote = 1;
            else
                data->flg.squote = 0;
            ret = 1;
        }
    }
    return (ret);
}

static void	ft_esc_symb(t_data *data, int x, int *i, char **insert)
{
	if (data->flg.squote)
        *insert = ft_charjoin(*insert, data->argv[x][*i]);
    else if (!data->flg.dquote || (data->flg.dquote && (data->argv[x][*i + 1] == 34 \
	|| data->argv[x][*i + 1] == 36 || data->argv[x][*i + 1] == 92 \
	|| data->argv[x][*i + 1] == 96)))
    {
        if (data->argv[x][*i + 1] == 36)
            data->flg.omit = 1;
        *i += 1;
        *insert = ft_charjoin(*insert, data->argv[x][*i]);
    }
    else
        *insert = ft_charjoin(*insert, data->argv[x][*i]);
}

static void ft_unpack_argv(t_data *data, int x, int i)
{
    char    *insert;
    char    *env;

    insert = ft_strdup("");
    while (data->argv[x][i])
    {
        if (ft_quotes(data, data->argv[x][i], 0))
            i++;
        else
        {
            if(data->argv[x][i] == 92)
				ft_esc_symb(data, x, &i, &insert);
            else if (data->argv[x][i] == 36 && !data->flg.omit && !data->flg.squote)
            {
                i += ft_insert_env(data, x, i + 1, &env);
				ft_str_handle(data, &insert, &env);
            }
            else if (((data->argv[x][i] == 34 && !data->flg.squote) || \
			(data->argv[x][i] == 39 && !data->flg.dquote)) || data->argv[x][i] != 92)
                insert = ft_charjoin(insert, data->argv[x][i]);
            i++;
        }
    }
	ft_set_argv(data, x, &insert);
}

void        ft_parser(t_data *data, int x)
{
    int i;

    data->flg.swap = 0;
    while (++x < data->argc)
    {
        i = -1;
		data->flg.dquote = 0;
    	data->flg.squote = 0;
    	data->flg.omit = 0;
        ft_unpack_argv(data, x, 0);
    }
    ft_sorter(data);
}