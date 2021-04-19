#include "minishell.h"

// void	ft_set_tokens(t_data *data, int x, int y, int i)
// {
// 	int	start;

// 	while (x < data->ccnt)
// 	{
// 		start = 0;
// 		y = 0;
// 		ft_splittkn(data, &start, x, y);
// 		x++;
// 	}
// 	i = 0;
// }

void	ft_set_commands(t_data *data, int x, int i)
{
	char *tmp;
	int	start;

	ft_initq(data);
	tmp = data->line;
	start = 0;
	while (data->line[i])
	{
		if (ft_splitcmd(data, i, &start, x))
			x++;
		i++;
	}
	// ft_set_tokens(data, 0, 0, 0);
	data->line = NULL;
	free(data->line);
}

void	ft_count_commands(t_data *data, int i)
{
	char	*tmp;

	ft_initq(data);
	data->ccnt = 1;
	tmp = data->line;
	while (tmp[i])
	{
		ft_ccnt(data, tmp, i);
		i++;
	}
	data->cmd = (t_command *)malloc(sizeof(t_command) * data->ccnt);
	if (data->cmd == NULL)
		printf("%s\n", strerror(errno));
	ft_set_commands(data, 0, 0);
}

void ft_line(t_data *data, char *str, int len)
{
	if (!data->line)
	{
		data->line = (char *)malloc(sizeof(char) * 2);
		data->line[0] = str[0];
		data->line[1] = '\0';
		data->linelen = len;
	}
	else
	{
		data->linelen += len;
		if (data->linelen > 0)
		{
			data->line = (char *)ft_realloc(data->line, (sizeof(char) * (data->linelen + 1)));
			if (len > 0)
				data->line[data->linelen - 1] = str[0];
			data->line[data->linelen] = '\0';
		}
		else
		{
			data->line = NULL;
			free(data->line);
		}
	}
}