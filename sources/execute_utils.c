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
