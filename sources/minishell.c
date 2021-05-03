#include "minishell.h"

void ft_init(t_data **data)
{
	if (!(*(data)))
		*data = (t_data *)malloc(sizeof(t_data));
	if (*data == NULL)
	{
		write(2, strerror(errno), sizeof(strerror(errno)));
		exit(1);
	}
	(*data)->line = NULL;
    (*data)->cmd = NULL;
    (*data)->argc = 0;
    (*data)->argv = NULL;
    (*data)->len = 0;
    (*data)->fd0 = 0;
    (*data)->fd1 = 1;
	(*data)->ret = 0;
}

void	ft_shell_prompt()
{
	write(2, "\033[1;34mminishell-> \033[0m", 23);
}

static void	ft_input(t_data *data)
{
	char	str[3];
	int		len;

	while (1)
	{	
		len = read(0, str, 3);
		if (str[0] == '\e' || !ft_strncmp(str, "\177", len))
			ft_termios(data, str, len);
		else
		{
			write(1, str, len);
			ft_line(data, str, len);
		}
		if (str[0] == '\n')
		{
			data->line[data->len - 1] = 0;
			if (data->line[0])
				add_hist(data->hist, data->line);
			ft_validate_line(data, -1);
			ft_shell_prompt();
			tputs(save_cursor, 1, &ft_putchar);
		}
		if (str[0] == '\4')
			break ;
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	*data;
	t_list	*env;
	t_hist	hist;

	env = envp_to_lst(envp);
	if (env == 0)
		return (1);
	hist.file = ft_strdup("minishell_history");
	if (hist.file == 0)
		return (2);
	hist.size = read_file(hist.file, &(hist.cmds));
	hist.pos = hist.size;

	if (argc != 1 && !argv[0])
	{
		ft_putendl_fd("bash: error: no parameters allowed\n", 2);
		return (1);
	}
	ft_init(&data);
	data->hist = &hist;
	data->env = env;
	ft_set_term(1);
	ft_shell_prompt();
	ft_input(data);
	return(0);
}
