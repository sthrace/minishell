#include "minishell.h"

static void		ft_splitt(t_data *data, int i, int start, int x)
{
	int len;

	ft_init_flags(data);
	len = 0;
	while (++x < data->command->argc)
	{
		while (data->cmd[i] == 32 && !data->quotes && !data->screen)
			i++;
		start = i;
		while (data->cmd[i] != 32 && data->cmd[i] != 10 && data->cmd[i] != 0)
		{
			ft_flagswitch(data, data->cmd[i]);
			while (data->quotes)
			{
				i++;
				len++;
				ft_flagswitch(data, data->cmd[i]);
			}
			i++;
			len++;
		}
		data->command->argv[x] = ft_substr(data->cmd, start, len);
		len = 0;
		i++;
	}
}

static void		ft_count(t_data *data, int i)
{
	data->command->argc = 0;
	ft_init_flags(data);
	while (data->cmd[i])
	{
		while (data->cmd[i] == 32)
			i++;
		ft_flagswitch(data, data->cmd[i]);
		if (data->cmd[i] != 32 && !data->quotes && !data->screen && ((data->cmd[i + 1] && data->cmd[i + 1] == 32) || data->cmd[i + 1] == 0))
			data->command->argc++;
		i++;
	}
}

static void		ft_splitter(t_data *data)
{
	if (!(data->command))
	{
		data->command = (t_command *)malloc(sizeof(t_command));
		if (!(data->command))
			ft_init(&data);
	}
	ft_count(data, 0);
	if (data->command->argc == 0)
		printf("syntax error near unexpected token `%c%c'\n", data->quotes, data->quotes);
	data->command->argv = (char **)malloc(sizeof(char *) * (data->command->argc + 1));
	data->command->type = (char *)malloc(sizeof(char) * data->command->argc);
	if (!data->command->argv || !data->command->type)
		ft_init(&data);
	ft_splitt(data, 0, 0, -1);
	ft_parser(data);
	data->cmd = NULL;
	free(data->cmd);
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
					len -= 1;
				data->cmd = ft_substr(line, start, len);
				start = i + 1;
				len = 0;
				ft_splitter(data);
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