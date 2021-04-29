#include "minishell.h"

void    ft_pipecount(t_data *data, char *cmd, int i)
{
    while (cmd[++i])
        if (cmd[i] == 124)
            data->cmds->pipes++;
    data->cmds->pipe = (t_pipe *)malloc(sizeof(t_pipe) * data->cmds->pipes);
    i = -1;
    while (++i < data->cmds->pipes)
        ft_reset_flags(data, 3, i);
    ft_reset_flags(data, 1, 0);
	cmd = ft_escapes(data, cmd, -1);
}

void    ft_pipe(t_data *data, char *cmd, int i, int start)
{
    ft_pipecount(data, cmd, -1);
	while (cmd[++i])
	{
		data->len++;
		if (ft_delimiter(data, cmd[i], 124) || !cmd[i + 1])
		{
			if (ft_delimiter(data, cmd[i], 124))
				data->len -= 1;
			data->cmd = ft_substr(cmd, start, data->len);
			start = i + 1;
			data->len = 0;
		}
	}
}

