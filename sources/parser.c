#include "minishell.h"

static void		ft_splitt(t_data *data, int i, int start, int x)
{
	int len;

	ft_init_flags(data);
	len = 1;
	while (data->cmd[i])
	{
		while (data->cmd[i] == 32 && !data->quotes && !data->screen)
			i++;
		ft_flagswitch(data, data->cmd[i]);
		if (data->cmd[i] != 32 && i > 0 && data->cmd[i - 1] == 32)
		{
			start = i;
			len = 1;
		}
		if (data->cmd[i] != 32 && !data->quotes && !data->screen && ((data->cmd[i + 1] && data->cmd[i + 1] == 32) || data->cmd[i + 1] == 0))
		{
			if (data->cmd[i] == 10)
				len -= 1;
			data->command->argv[x] = ft_substr(data->cmd, start, len);
			printf("Token %d: %s\n", x, data->command->argv[x]);
			len = 0;
			x++;
		}
		i++;
		len++;
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

void		ft_parser(t_data *data)
{
	if (!(data->command))
	{
		data->command = (t_command *)malloc(sizeof(t_command));
		if (!(data->command))
			ft_init(&data);
	}
	ft_count(data, 0);
	data->command->argv = (char **)malloc(sizeof(char *) * (data->command->argc + 1));
	if (!data->command->argv)
		ft_init(&data);
	ft_splitt(data, 0, 0, 0);
	data->cmd = NULL;
	free(data->cmd);
}