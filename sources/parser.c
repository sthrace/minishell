#include "minishell.h"

void        ft_splits(t_data *data, char *cmd, int i, int x)
{
    int start;

    data->len = 0;
	while (++x < data->cmds->argc)
	{
		while (cmd[i] == 32)
			i++;
		start = i;
		while (cmd[i] != 32 && cmd[i] != 0)
		{
			ft_flagswitch(data, cmd[i], 0);
			while (data->quotes)
			{
                ft_increment(data, &i);
				ft_flagswitch(data, cmd[i], 0);
			}
            ft_increment(data, &i);
		}
		data->cmds->argv[x] = ft_substr(cmd, start, data->len);
		data->len = 0;
		i++;
        data->cmds->argv[x] = ft_quotes(data, data->cmds->argv[x], -1);
	}
}

void        ft_simple(t_data *data, char *cmd, int i)
{
    ft_check_redirect(data, cmd, -1);
    ft_init_flags(data);
	while (cmd[++i])
	{
		while (cmd[i] == 32)
			i++;
        if (!cmd[i])
            break ;
		ft_flagswitch(data, cmd[i], 0);
		if (cmd[i] != 32 && !data->quotes && ((cmd[i + 1] && cmd[i + 1] == 32) || cmd[i + 1] == 0))
			data->cmds->argc++;
	}
    data->cmds->argv = (char **)malloc(sizeof(char *) * (data->cmds->argc + 1));
    data->cmds->argv[data->cmds->argc] = NULL;
    if (!data->cmds->argv)
    {
        printf("%s\n", strerror(errno));
        return ;
    }
    if (ft_strchr(cmd, '$'))
        cmd = ft_insert_env(data, cmd, -1, 0);
    ft_init_flags(data);
    ft_splits(data, cmd, 0, -1);
    ft_sorter(data, data->cmds->argc, data->cmds->argv);
}

void        ft_parser(t_data *data, char *command)
{
    if (ft_strchr(command, '|'))
        ft_pipe(data, command, -1);
    else
    {
        data->cmds = (t_cmd *)malloc(sizeof(t_cmd));
        if (!data->cmds)
        {
            printf("%s\n", strerror(errno));
            return ;
        }
        else
        {
            data->cmds->argc = 0;
            data->len = 0;
            data->cmds->rread = 0;
            data->cmds->rwrite = 0;
            ft_close_fd(data, 2);
            data->cmds->fdnum = 0;
            ft_simple(data, command, -1);
        }
    }
}