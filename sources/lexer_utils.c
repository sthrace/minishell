#include "minishell.h"

void	ft_init_quotes(t_data *data, char **output, char **stripped, int t)
{
	if (t == 0)
	{
		ft_init_flags(data);
		*output = NULL;
		data->start = -1;
	}
	else if (t == 1)
	{
		*output = ft_strjoin(*output, *stripped);
		free(*stripped);
		data->len = 0;
		data->quotes = 0;
		data->start = -1;
	}
}

char		*ft_quotes(t_data *data, char *command, int i)
{
	char	*stripped;
	char	*output;

	ft_init_quotes(data, &output, &stripped, 0);
	if (!(ft_strchr(command, '\'')) && !(ft_strchr(command, '"')))
		return (command);
	while (command[++i])
	{
		ft_flagswitch(data, command[i], 1);
		if (data->quotes)
		{
			if (!output)
				output = ft_substr(command, 0, i);
			if (data->start == -1)
				data->start = i + 1;
			while (command[i] != data->quotes)
				ft_increment(data, &i);
		}
		if (data->len > 0)
		{
			stripped = ft_substr(command, data->start, data->len);
			ft_init_quotes(data, &output, &stripped, 1);
		}
	}
	free(command);
	return (output);
}

static char	*ft_escapes_tool(char *command, int i)
{
	char	*temp;
	char	*suffix;

	command[i] = 0;
	suffix = ft_strdup(&command[i + 1]);
	temp = ft_strjoin(command, suffix);
	free(command);
	command = ft_strdup(temp);
	free(temp);
	free(suffix);
	return (command);
}

char		*ft_escapes(t_data *data, char *command, int i)
{
	ft_init_flags(data);
	while (command[++i])
	{
		ft_flagswitch(data, command[i], 1);
		if (data->escape && !data->quotes && command[i + 1])
			command = ft_escapes_tool(command, i);
		else if (data->escape && data->quotes == 34 && command[i + 1])
		{
			if (command[i + 1] == 34 || command[i + 1] == 36 || command[i + 1] == 92 || command[i + 1] == 96)
				command = ft_escapes_tool(command, i);
		}
		if (data->escape && command[i + 1] && command[i + 1] != 92)
			data->escape = 0;
	}
	return (command);
}