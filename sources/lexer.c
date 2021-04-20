#include "minishell.h"

void	ft_set_tokens(t_data *data, int x)
{
	int	start;

	ft_initqt(data, 0);
	while (++x < data->ccnt)
	{
		start = 0;
		ft_splittkn(data, data->cmd[x].arg, x, &start);
	}
}

void	ft_count_tokens(t_data *data, int i, int x)
{
	char	*tmp;

	ft_initqt(data, 2);
	while (++x < data->ccnt)
	{
		i = 0;
		tmp = data->cmd[x].arg;
		ft_tcnt(data, tmp, i, x);
		data->cmd[x].token = (t_token *)malloc(sizeof(t_token) * data->cmd[x].tcnt);
		if (data->cmd[x].token == NULL)
			printf("%s\n", strerror(errno));
	}	
	ft_set_tokens(data, -1);
}

void	ft_set_commands(t_data *data, int x, int i)
{
	int	start;

	ft_initqt(data, 0);
	start = 0;
	while (data->line[i])
	{
		if (ft_splitcmd(data, i, &start, x))
			x++;
		i++;
	}
	ft_count_tokens(data, 0, -1);
	data->line = NULL;
	free(data->line);
}

void	ft_count_commands(t_data *data, int i)
{
	char	*tmp;

	ft_validator(data);
	ft_initqt(data, 0);
	data->ccnt = 1;
	tmp = data->line;
	while (tmp[++i])
		ft_ccnt(data, tmp, i);
	data->cmd = (t_command *)malloc(sizeof(t_command) * data->ccnt);
	if (data->cmd == NULL)
		printf("%s\n", strerror(errno));
	ft_set_commands(data, 0, 0);
}
