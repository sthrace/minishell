#include "minishell.h"

void	ft_cmd_split(t_data *data, int i, int len, int start)
{
	int		x;

	x = -1;
	
	while (++x < data->argc)
	{
		ft_flags(data, '\0', 0);
		while (data->cmd[i] == 32)
			i++;
		start = i;
		while (data->cmd[i] != 32 && data->cmd[i])
		{
			ft_flags(data, data->cmd[i], 1);
			while (data->flg.quotes && data->cmd[i])
			{
                len++;
    			i += 1;
				ft_flags(data, data->cmd[i], 1);
			}
			if (data->cmd[i] == 0)
				break ;
            len++;
    		i += 1;
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
	while (data->cmd[++i] == 32)
			;
	while (data->cmd[i])
	{
		ft_flags(data, data->cmd[i], 1);
		if (data->cmd[i] == 32 && data->cmd[i + 1] != 32 && data->cmd[i + 1] && !data->flg.quotes && !data->flg.esc)
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

void	ft_crossroads(t_data *data)
{
	if (!(ft_strchr(data->cmd, '|')))
	{
		ft_check_redirects(data, -1);
		ft_cmd_count(data, -1);
		ft_cmd_split(data, 0, 0, 0);
		ft_flags(data, '\0', 0);
		ft_parser(data, -1);
	}
	else
		printf("piped command\n");
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
        if (data->line[i] == 59 && !data->flg.quotes && !data->flg.esc)
		{
			data->cmd = ft_substr(data->line, start, len);
			start = i + 1;
			len = 0;
			ft_crossroads(data);
			free(data->cmd);
		}
		len++;
	}
	data->cmd = ft_substr(data->line, start, len);
	ft_crossroads(data);
	free(data->cmd);
	free(data->line);
	data->line = NULL;
}

void 	ft_line(t_data *data, char *str, int len)
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
			data->len = 0;
			data->line = NULL;
			free(data->line);
		}
	}
}