#include "minishell.h"

void	ft_abs_path(t_data *data, char **file)
{
	struct stat	buf[4096];

	*file = ft_strdup(data->argv[0]);
	data->ret = stat(*file, buf);
	if (data->ret == -1)
		printf("bash: %s: %s\n", *file, strerror(errno));
	if (data->pl->state == 0)
		ft_execute(data, *file);
	else
		data->pl->pids[data->pl->count - 1] = execute_pipe(data, *file, 0);
}

void	ft_exectool(t_data *data, char ***paths, char **file)
{
	ft_free_array(*paths);
	if (data->ret == -1 || !*paths)
	{
		data->ret = 127;
		printf("bash: %s: %s\n", data->argv[0], strerror(errno));
	}
	else if (data->pl->state == 0)
		ft_execute(data, *file);
	if (data->pl->state != 0)
		data->pl->pids[data->pl->count - 1] = execute_pipe(data, *file, 0);
}

int	pipe_fork(t_data *data, char *file, int builtin)
{
	if (data->fd0 != STDIN || data->fd1 != STDOUT)
	{
		if (data->fd0 != STDIN && (data->pl->state > 1 || \
		data->pl->state < 0))
			dup2(data->fd0, STDIN);
		if (data->fd1 != STDOUT && data->pl->state > 0)
			dup2(data->fd1, STDOUT);
	}
	else
	{
		if (data->pl->state > 0)
		{
			dup2(data->pl->fdout[WR], STDOUT);
			close(data->pl->fdout[RD]);
		}
		if (data->pl->state > 1 || data->pl->state < 0)
		{
			dup2(data->pl->fdin[RD], STDIN);
			close(data->pl->fdout[WR]);
		}
	}
	if (builtin)
		exit(ft_sorter(data));
	else
		exit(execve(file, data->argv, env_to_arr(data->env)));
}
