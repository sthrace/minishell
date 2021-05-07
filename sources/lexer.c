#include "minishell.h"

void	ft_cmd_split(t_data *data, int i, int len, int x)
{
	int		start;

	while (++x < data->argc)
	{
		ft_flags(data, '\0', 0);
		while (data->cmd[i] == ' ')
			i++;
		start = i;
		while (data->cmd[i] != ' ' && data->cmd[i])
		{
			ft_flags(data, data->cmd[i], 1);
			while (data->flg.quotes && data->cmd[i])
			{
				ft_pointer_inc(&len, &i);
				ft_flags(data, data->cmd[i], 1);
			}
			if (data->cmd[i] == 0)
				break ;
			ft_pointer_inc(&len, &i);
		}
		data->argv[x] = ft_substr(data->cmd, start, len);
		len = 0;
		i++;
	}
}

void	ft_cmd_count(t_data *data, int i)
{
	ft_flags(data, '\0', 0);
	data->argc = 1;
	while (data->cmd[++i] == ' ')
		;
	while (data->cmd[i])
	{
		ft_flags(data, data->cmd[i], 1);
		if (data->cmd[i] == ' ' && data->cmd[i + 1] != ' ' && data->cmd[i + 1] \
		&& !data->flg.quotes && !data->flg.esc)
			data->argc++;
		i++;
	}
	data->argv = (char **)malloc(sizeof(char *) * (data->argc + 1));
	data->argv[data->argc] = NULL;
	if (!data->argv)
	{
		printf("%s\n", strerror(errno));
		ft_init(&data);
		return ;
	}
}

void	check_pipes(t_data *data, int i)
{
	if (data->line[i] == '|' || data->pl->state > 0)
	{
		data->pl->state++;
		data->pl->count++;
	}
	if (!(data->line[i] == '|') && data->pl->state > 0)
		data->pl->state *= -1;
}

void	ft_crossroads(t_data *data)
{
	ft_check_redirects(data, -1);
	ft_cmd_count(data, -1);
	ft_cmd_split(data, 0, 0, -1);
	ft_flags(data, '\0', 0);
	ft_parser(data, -1);

	if (is_cmd_bltin(data))
		ft_free_array(data->argv);
		
	if (data->pl->state < 0)
	{
		while (data->pl->count--)
		{
			waitpid(data->pl->pids[data->pl->count], &data->ret, 0);
			// if (data->ret == 65280)
			// 	printf("Command not found\n");
		}
		data->pl->state = 0;
		data->pl->count = 0;
	}
}

void	ft_get_cmd(t_data *data, int i)
{
	int		start;
	int		len;

	start = 0;
	len = 0;
	while (data->line[++i])
	{
		ft_flags(data, data->line[i], 1);
		if ((data->line[i] == ';' || data->line[i] == '|') && !data->flg.quotes && !data->flg.esc)
		{
			check_pipes(data, i);
			data->cmd = ft_substr(data->line, start, len);
			start = i + 1;
			len = -1;
			ft_crossroads(data);
			free(data->cmd);
		}
		len++;
	}
	check_pipes(data, i);
	data->cmd = ft_substr(data->line, start, len);
	ft_crossroads(data);
	free(data->cmd);
	free(data->line);
	data->line = NULL;
}

void 	ft_line(t_data *data, char *str, int len)
{
	write(1, str, len);
	if (g_sig == 1)
	{
		ft_line_handler(data, str, len, 3);
		g_sig = 0;
	}
	if (!data->line)
		ft_line_handler(data, str, len, 1);
	else
	{
		data->len += len;
		if (data->len > 0)
			ft_line_handler(data, str, len, 2);
		else
			ft_line_handler(data, str, len, 3);
	}
}
