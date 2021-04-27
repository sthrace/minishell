#include "minishell.h"

static void ft_sorter(t_data *data, int argc, char **argv)
{
    if (!(ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "ECHO", ft_strlen(argv[0]))))
        ft_echo(argc, argv);
    else if (!(ft_strncmp(argv[0], "cd", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "CD", ft_strlen(argv[0]))))
        ft_cd(argc, argv);
    else if (!(ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "PWD", ft_strlen(argv[0]))))
        ft_pwd();
    // else if (!(ft_strncmp(argv[0], "export", ft_strlen(argv[0]))))
    //     ft_export(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "unset", ft_strlen(argv[0]))))
    //     ft_unset(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "env", ft_strlen(argv[0]))))
    //     ft_env(data, argc, argv);
    else if (!(ft_strncmp(argv[0], "exit", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "EXIT", ft_strlen(argv[0]))))
        ft_exit(data, argc, argv, -1);
    else
        ft_binsearch(argv);
}

void    ft_pipe(t_data *data, char *cmd, int i)
{
    data->len = 0;
    cmd = NULL;
    i = 0;
}

void        ft_splits(t_data *data, char *cmd, int i, int x)
{
    int start;

	data->len = 0;
    ft_init_flags(data);
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
    data->cmds->argc = 0;
	ft_init_flags(data);
	while (cmd[i])
	{
		while (cmd[i] == 32)
			i++;
		ft_flagswitch(data, cmd[i], 0);
		if (cmd[i] != 32 && !data->quotes && !data->escape && ((cmd[i + 1] && cmd[i + 1] == 32) || cmd[i + 1] == 0))
			data->cmds->argc++;
		i++;
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
            ft_simple(data, command, 0);
    }
}