#include "minishell.h"

int	ft_func_env(t_data *data, char **env, int x, int i)
{
	if (data->argv[x][i] == '$')
	{
		data->ret = 0;
		*env = ft_strdup("$");
		return (0);
	}
	if (!data->argv[x][i] || (data->flg.dquote && data->argv[x][i] == '"'))
	{
		data->ret = 0;
		*env = ft_strdup("$");
		return (1);
	}
	return (0);
}

void	ft_set_argv(t_data *data, int x, char **insert)
{
	free(data->argv[x]);
	data->argv[x] = ft_strdup(*insert);
	free(*insert);
}

void	ft_str_handle(t_data *data, char **insert, char **env)
{
	char	*temp;

	temp = *insert;
	*insert = ft_strjoin(temp, *env);
	free(temp);
	data->flg.omit = 0;
}

void	ft_crossroads(t_data *data)
{
	ft_check_redirects(data, -1);
	ft_cmd_count(data, -1);
	ft_cmd_split(data, 0, 0, -1);
	ft_flags(data, '\0', 0);
	ft_parser(data, -1);
	if (is_cmd_bltin(data))
		ft_free_array(data->argv);
	if (data->pl->state < 0)
	{
		while (data->pl->count--)
			waitpid(data->pl->pids[data->pl->count], &data->ret, 0);
		data->pl->state = 0;
		data->pl->count = 0;
	}
}

char	**ft_split_path(t_data *data)
{
	char	**paths;

	if (!get_var(data->env, "PATH"))
	{
		data->ret = 127;
		printf("bash: No such file or directory\n");
		return (0x0);
	}
	paths = ft_split(get_var(data->env, "PATH"), ':');
	if (!paths)
	{
		data->ret = 127;
		printf("bash: %s\n", strerror(errno));
		return (0x0);
	}
	return (paths);
}
