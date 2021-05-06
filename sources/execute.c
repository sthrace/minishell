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
		ft_set_term(2);
		if (data->ret && errno == EACCES)
			printf("bash: %s: %s\n", file, strerror(errno));
		exit(data->ret);
	}
	wait(&data->ret);
	signal(SIGQUIT, &sig_handler);
	if (WIFEXITED(data->ret))
		data->ret = WEXITSTATUS(data->ret);
	ft_free_array(data->argv);
	free(data->argv);
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

void	ft_binsearch(t_data *data, int cnt, char *dir, char *file)
{
	char		**paths;
	struct stat	buf[4096];

	paths = ft_split_path(data);
	if (data->argv[0][0] == 46 || data->argv[0][0] == 47)
		ft_execute(data, ft_strdup(data->argv[0]));
	else if (paths)
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
		ft_free_array(paths);
		if (data->ret == -1 || !paths)
			printf("bash: %s: %s\n", data->argv[0], strerror(errno));
		if (data->ret != -1)
			ft_execute(data, file);
	}
}

void	ft_sorter(t_data *data)
{
	int	i;

	i = 1;
	if ((!(ft_strncmpul(data->argv[0], "echo", 4))) && !data->argv[0][4])
		ft_echo(data);
	else if ((!(ft_strncmpul(data->argv[0], "cd", 2))) && !data->argv[0][2])
		ft_cd(data, 0, NULL, NULL);
	else if ((!(ft_strncmpul(data->argv[0], "pwd", 3))) && !data->argv[0][3])
		ft_pwd();
	else if ((!(ft_strncmpul(data->argv[0], "export", 6))) && \
			!data->argv[0][6] && data->argc == 1)
		print_export(data->env);
	else if ((!(ft_strncmpul(data->argv[0], "export", 6))) && !data->argv[0][6])
		while (data->argv[i])
			set_var(&data->env, data->argv[i++], 0);
	else if ((!(ft_strncmpul(data->argv[0], "unset", 5))) && !data->argv[0][5])
		while (data->argv[i])
			unset_var(&data->env, data->argv[i++]);
	else if ((!(ft_strncmpul(data->argv[0], "env", 3))) && !data->argv[0][3])
		print_env(data->env);
	else if ((!(ft_strncmpul(data->argv[0], "exit", 4))) && !data->argv[0][4])
		ft_exit(data, -1);
	else
		ft_binsearch(data, -1, NULL, NULL);
	ft_free_array(data->argv);
}
