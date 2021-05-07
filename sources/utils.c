#include "minishell.h"

void	ft_set_argv(t_data *data, int x, char **insert)
{
	free(data->argv[x]);
    data->argv[x] = ft_strdup(*insert);
	free(*insert);
}

void	ft_str_handle(t_data *data, char **insert, char **env)
{
	char	*temp;

	temp = *insert;
    *insert = ft_strjoin(temp, *env);
    free(temp);
    data->flg.omit = 0;
}

void	ft_pointer_inc(int *a, int *b)
{
	*a += 1;
	*b += 1;
}

void	ft_line_handler(t_data *data, char *str, int len, int type)
{
	if (type == 1)
	{
		data->line = (char *)malloc(sizeof(char) * 2);
		data->line[0] = str[0];
		data->line[1] = '\0';
		data->len = len;
	}
	else if (type == 2)
	{
		data->line = (char *)ft_realloc(data->line, (sizeof(char) * \
		(data->len + 1)));
		if (len > 0)
			data->line[data->len - 1] = str[0];
		data->line[data->len] = '\0';
	}
	else if (type == 3)
	{
		data->len = 0;
		free(data->line);
		data->line = NULL;
	}
}

int		ft_free_array(char **array)
{
	int	cnt;

	cnt = 0;
	if (!array)
		return (1);
	while (array[cnt])
	{
		free(array[cnt]);
		cnt++;
	}
	free(array);
	return (0);
}
