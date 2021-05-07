#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[4096];

	printf("%s\n", getcwd(buf, 4096));
}

void	ft_set_dir(t_data *data, char **newdir, char **pwd)
{
	char	buf[4096];

	free(*newdir);
	*pwd = ft_strjoin("PWD=", getcwd(buf, 4096));
	if (get_var(data->env, "PWD"))
		set_var(&data->env, *pwd, 0);
	free(*pwd);
}

void	ft_cd(t_data *data, int ret, char *pwd, char *oldpwd)
{
	char	buf[4096];
	char	*newdir;
	char	*temp;

	if (get_var(data->env, "OLDPWD") || data->flg.opwd)
	{
		temp = ft_strdup(getcwd(buf, 4096));
		oldpwd = ft_strjoin("OLDPWD=", temp);
		free(temp);
		set_var(&data->env, oldpwd, 0);
		free(oldpwd);
		data->flg.opwd = 0;
	}
	if (data->argc == 1 && get_var(data->env, "HOME"))
		newdir = ft_strdup(get_var(data->env, "HOME"));
	else if (data->argc == 1 && !get_var(data->env, "HOME"))
	{
		printf("bash: cd: HOME not set\n");
		return ;
	}
	else if (data->argc == 2)
		newdir = ft_strdup(data->argv[1]);
	ret = chdir(newdir);
	if (ret == -1)
	{
		printf("bash: cd: %s: %s\n", newdir, strerror(errno));
		return ;
	}
	ft_set_dir(data, &newdir, &pwd);
}

void	ft_echo(t_data *data)
{
	int		i;
	short	n;

	i = 1;
	n = 0;
	if (data->argc > 1 && (!(ft_strncmp(data->argv[1], "-n", 2))))
		n = 1;
	while (i < data->argc)
	{
		while (!(ft_strncmp(data->argv[i], "-n", 2)) && data->argv[i + 1])
			i++;
		if (data->argv[i])
		{
			if (ft_strncmp(data->argv[i], "-n", 2))
			{
				write(data->fd1, data->argv[i], ft_strlen(data->argv[i]));
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
				data->ret = 255;
				printf("exit\nbash: exit: %s: \
				numeric argument required\n", data->argv[1]);
			}
		}
	}
	if (data->argc > 2 && data->ret != 2)
	{
		data->ret = 1;
		printf("exit\nbash: exit: too many arguments\n");
		return ;
	}
	if (data->ret != 2)
	{
		if (data->argc > 1)
			data->ret = ft_atoi(data->argv[1]);
		printf("exit\n");
	}
	if (data->ret == 1 || data->ret == 2)
		exit(data->ret);
	else
		exit(0);
}
