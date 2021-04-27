#include "minishell.h"

void		ft_splitcmd(t_data *data, char *line, int i, int len)
{
	int		start;

	if (!ft_validate(data, line))
	{
		ft_init_flags(data);
		start = 0;
		line = ft_escapes(data, line, -1);
		while (line[++i])
		{
			len++;
			if (ft_semicolumn(data, line[i]) || !line[i + 1])
			{
				if (ft_semicolumn(data, line[i]))
					len -= 1;
				data->cmd = ft_substr(line, start, len);
				ft_parser(data, data->cmd);
				start = i + 1;
				len = 0;
				if (line[i + 1] == 10)
					break ;
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