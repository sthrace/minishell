#include "minishell.h"

void	line_tool(t_data *data, int type)
{
	if (type == 1)
	{
		ft_validate_line(data, -1);
		ft_shell_prompt();
		tputs(save_cursor, 1, &ft_putchar);
	}
	if (type == 2)
	{
		printf("exit\n");
		ft_set_term(2);
	}
}

void	validator_err(t_data *data, int i)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	if (data->line[i + 1] && data->line[i + 1] == data->line[i])
		write(2, &data->line[i], 1);
	write(2, &data->line[i], 1);
	write(2, "'\n", 2);
}

void	ft_pointer_inc(int *a, int *b)
{
	*a += 1;
	*b += 1;
}

void	ft_line_handler(t_data *data, char *str, int len, int type)
{
	if (type == 1)
	{
		data->line = (char *)malloc(sizeof(char) * 2);
		data->line[0] = str[0];
		data->line[1] = '\0';
		data->len = len;
	}
	else if (type == 2)
	{
		data->line = (char *)ft_realloc(data->line, (sizeof(char) * \
		(data->len + 1)));
		if (len > 0)
			data->line[data->len - 1] = str[0];
		data->line[data->len] = '\0';
	}
	else if (type == 3)
	{
		g_sig = 0;
		data->ret = 1;
		data->len = 0;
		free(data->line);
		data->line = NULL;
	}
}

int	ft_free_array(char **array)
{
	int	cnt;

	cnt = 0;
	if (!array)
		return (1);
	while (array[cnt])
	{
		free(array[cnt]);
		cnt++;
	}
	free(array);
	return (0);
}
