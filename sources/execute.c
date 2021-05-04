#include "minishell.h"

// static void	ft_execute(t_data *data, char *file)
// {
// 	extern char	**environ;

// 	signal(SIGINT, &child_sig_handler);
// 	signal(SIGQUIT, &child_sig_handler);
// 	if (!fork())
// 	{
// 		if (data->fd0 > 0)
// 			dup2(data->fd0, 0);
// 		if (data->fd1 > 1)
// 			dup2(data->fd1, 1);
// 		data->ret = execve(file, data->argv, environ);
// 		if (data->ret && errno == EACCES)
// 			printf("bash: %s: %s\n", file, strerror(errno));
// 		exit(data->ret);
// 	}
// 	wait(&data->ret);
// 	if (WIFEXITED(data->ret))
// 		data->ret = WEXITSTATUS(data->ret);
// }

int	ft_execute(t_data *data, char *file)
{
	extern char	**environ;

	data->pl->fdin[0] = data->pl->fdout[0];
	data->pl->fdin[1] = data->pl->fdout[1];
	if (data->pl->pipenum > 0)
		pipe(data->pl->fdout);

	int pid = fork();
	if (pid == 0)
	{
		// Child thread
		if (data->pl->pipenum  > 0)								// fdout != 0
		{
			dup2(data->pl->fdout[1], 1);
			close(data->pl->fdout[0]);
		}
		if (data->pl->pipenum  > 1 || data->pl->pipenum  < 0)	// fdin != 0
			dup2(data->pl->fdin[0], 0);
		exit(execve(file, data->argv, environ));
	}
	// Parent thread
	if (data->pl->pipenum  > 0)									// fdout != 0
		close(data->pl->fdout[1]);
	if (data->pl->pipenum  > 1 || data->pl->pipenum  < 0)		// fdin != 0
		close(data->pl->fdin[0]);
	return (pid);
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
			if (!data->ret)
				break ;
			free(file);
		}
		if (data->ret == -1)
			printf("bash: %s: command not found\n", data->argv[0]);
		ft_free_array(paths);
		if (data->ret != -1)
		{
			int i;
			i  = data->pl->pipenum;
			if (data->pl->pipenum < 0)
				i = data->pl->pipenum * -1 + 1;
			data->pl->pids[i] = ft_execute(data, file);
		}
	}
}

void	ft_sorter(t_data *data)
{
	int	i;

	if ((!(ft_strncmp(data->argv[0], "echo", 4)) || \
	!(ft_strncmp(data->argv[0], "ECHO", 4))) && \
	ft_strlen(data->argv[0]) == 4)
		ft_echo(data);
	else if ((!(ft_strncmp(data->argv[0], "cd", 2)) || \
	!(ft_strncmp(data->argv[0], "CD", 2))) && \
	ft_strlen(data->argv[0]) == 2)
		ft_cd(data);
	else if ((!(ft_strncmp(data->argv[0], "pwd", 3)) || \
	!(ft_strncmp(data->argv[0], "PWD", 3))) && \
	ft_strlen(data->argv[0]) == 3)
		ft_pwd();
	else if ((!(ft_strncmp(data->argv[0], "export", 6)) || \
	!(ft_strncmp(data->argv[0], "EXPORT", 6))) && \
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
	else if ((!(ft_strncmp(data->argv[0], "unset", 5)) || \
	!(ft_strncmp(data->argv[0], "UNSET", 5))) && \
	ft_strlen(data->argv[0]) == 5)
	{
		i = 1;
		while (data->argv[i])
			unset_var(&data->env, data->argv[i++]);
	}
	else if ((!(ft_strncmp(data->argv[0], "env", 3)) || \
	!(ft_strncmp(data->argv[0], "ENV", 3))) && \
	ft_strlen(data->argv[0]) == 3)
		print_env(data->env);
	else if ((!(ft_strncmp(data->argv[0], "exit", 4)) || \
	!(ft_strncmp(data->argv[0], "EXIT", 4))) && \
	ft_strlen(data->argv[0]) == 4)
		ft_exit(data, -1);
	else
		ft_binsearch(data, -1, NULL);
	free(data->argv);
}
