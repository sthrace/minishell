#include "minishell.h"

static void	ft_execute(t_data *data, char *file)
{
	extern char	**environ;

	signal(SIGINT, &child_sig_handler);
	signal(SIGQUIT, &child_sig_handler);
	if (!fork())
	{
		if (data->fd0 > 0)
			dup2(data->fd0, 0);
		if (data->fd1 > 1)
			dup2(data->fd1, 1);
		data->ret = execve(file, data->argv, environ);
		if (data->ret && errno == EACCES)
			printf("bash: %s: %s\n", file, strerror(errno));
		exit(data->ret);
	}
	wait(&data->ret);
	if (WIFEXITED(data->ret))
		data->ret = WEXITSTATUS(data->ret);
}

static char	**ft_split_path(t_data *data)
{
	char	**paths;

	if (!get_var(data->env, "PATH"))
	{
		printf("bash: %s\n", strerror(errno));
		return (0x0);
	}
	paths = ft_split(get_var(data->env, "PATH"), ':');
	if (!paths)
	{
		printf("bash: %s\n", strerror(errno));
		return (0x0);
	}
	return (paths);
}

void	ft_binsearch(t_data *data, int cnt, char *dir)
{
	char		**paths;
	char		*file;
	struct stat	buf[4096];

	paths = ft_split_path(data);
	if (!paths)
		return ;
	if (data->argv[0][0] == 46 || data->argv[0][0] == 47)
		ft_execute(data, ft_strdup(data->argv[0]));
	else
	{
		while (paths[++cnt])
		{
			dir = ft_strjoin(paths[cnt], "/");
			file = ft_strjoin(dir, data->argv[0]);
			free(dir);
			data->ret = stat(file, buf);
			free(file);
			if (!data->ret)
				break ;
		}
		if (data->ret == -1)
			printf("bash: %s: command not found\n", data->argv[0]);
		ft_free_array(paths);
		if (data->ret != -1)
			ft_execute(data, file);
	}
}

void	ft_sorter(t_data *data)
{
	int	i;

	if ((!(ft_strncmp_case(data->argv[0], "echo", 4))) && \
	ft_strlen(data->argv[0]) == 4)
		ft_echo(data);
	else if ((!(ft_strncmp_case(data->argv[0], "cd", 2))) && \
	ft_strlen(data->argv[0]) == 2)
		ft_cd(data);
	else if ((!(ft_strncmp_case(data->argv[0], "pwd", 3))) && \
	ft_strlen(data->argv[0]) == 3)
		ft_pwd();
	else if ((!(ft_strncmp_case(data->argv[0], "export", 6))) && \
	ft_strlen(data->argv[0]) == 6)
	{
		if (data->argc == 1)
			print_export(data->env);
		else
		{
			i = 1;
			while (data->argv[i])
				set_var(&data->env, data->argv[i++], 0);
		}
	}
	else if ((!(ft_strncmp_case(data->argv[0], "unset", 5))) && \
	ft_strlen(data->argv[0]) == 5)
	{
		i = 1;
		while (data->argv[i])
			unset_var(&data->env, data->argv[i++]);
	}
	else if ((!(ft_strncmp_case(data->argv[0], "env", 3))) && \
	ft_strlen(data->argv[0]) == 3)
		print_env(data->env);
	else if ((!(ft_strncmp_case(data->argv[0], "exit", 4))) && \
	ft_strlen(data->argv[0]) == 4)
		ft_exit(data, -1);
	else
		ft_binsearch(data, -1, NULL);
	ft_free_array(data->argv);
}
