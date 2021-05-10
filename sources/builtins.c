#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	buf[4096];
	char	*pwd;

	pwd = getcwd(buf, 4096);
	write(data->fd1, pwd, ft_strlen(pwd));
	write(data->fd1, "\n", 1);
}

void	ft_echo(t_data *data, int i, int n)
{
	if (data->argc > 1 && (!(ft_strncmp(data->argv[1], "-n", 2))))
	{
		n = 1;
		data->flg.n = 1;
		tputs(save_cursor, 1, &ft_putchar);
	}
	while (i < data->argc)
	{
		while (!(ft_strncmp(data->argv[i], "-n", 2)) && data->argv[i + 1])
			i++;
		if (data->argv[i])
		{
			if (ft_strncmp(data->argv[i], "-n", 2))
			{
				write(data->fd1, data->argv[i], ft_strlen(data->argv[i]));
				if (i < data->argc - 1)
					write(data->fd1, " ", 1);
			}
		}
		i++;
	}
	if (!n)
		write(data->fd1, "\n", 1);
}

void	ft_exit(t_data *data, int i)
{
	if (data->argc > 1)
	{
		while (data->argv[1][++i])
		{
			if (!(ft_isdigit(data->argv[1][i])))
			{
				printf("exit\nbash: exit: ");
				printf("%s: numeric argument required\n", data->argv[1]);
				exit(255);
			}
		}
		if (data->argc > 2)
		{
			data->ret = 1;
			printf("exit\nbash: exit: too many arguments\n");
			return ;
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(data->argv[1]));
		}
	}
	else
		exit(0);
}
