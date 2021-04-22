#include "minishell.h"

int    ft_semicolumn(t_data *data, char c)
{
    ft_flagswitch(data, c);
    if (c == 59 && !data->quotes && !data->screen)
        return (1);
    return (0);
}

void		ft_splitcmd(t_data *data, char *line, int i, int len)
{
	int		start;

	if (!ft_validate(data, line))
	{
		ft_init_flags(data);
		start = 0;
		while (line[++i])
		{
			len++;
			if (ft_semicolumn(data, line[i]) || !line[i + 1])
			{
				if (ft_semicolumn(data, line[i]))
				{
					data->cmd = ft_substr(line, start, len - 1);
					start = i + 1;
					len = 0;
				}
				else
					data->cmd = ft_substr(line, start, len);
				ft_parser(data);
			}
		}
	}
	data->line = NULL;
	free(data->line);
}

void ft_line(t_data *data, char *str, int len)
{
	if (!data->line)
	{
		data->line = (char *)malloc(sizeof(char) * 2);
		data->line[0] = str[0];
		data->line[1] = '\0';
		data->len = len;
	}
	else
	{
		data->len += len;
		if (data->len > 0)
		{
			data->line = (char *)ft_realloc(data->line, (sizeof(char) * (data->len + 1)));
			if (len > 0)
				data->line[data->len - 1] = str[0];
			data->line[data->len] = '\0';
		}
		else
		{
			data->line = NULL;
			free(data->line);
		}
	}
}