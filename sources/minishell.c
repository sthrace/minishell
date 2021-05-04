#include "minishell.h"

void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
		write(2, "^\\\n", 3);
	if (sig == SIGQUIT)
		write(2, "^\\Quit: 3\n", 10);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(2, "\033[1;34m\nminishell-> \033[0m", 24);
}

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
}

void	ft_shell_prompt()
{
	write(2, "\033[1;34mminishell-> \033[0m", 23);
}

static void	ft_input(t_data *data)
{
	char	str[3];
	int		len;

	data->ret = 0;
	
	signal(SIGQUIT, &sig_handler);
	while (1)
	{	
		signal(SIGINT, &sig_handler);
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
		{
			printf("exit\n");
			ft_set_term(2);
			break ;
		}
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	*data;
	t_list	*env;
	t_hist	hist;
	t_pipeline pl;

	env = envp_to_lst(envp);
	init_hist(&hist);
	pl.pipenum = 0;

	if (argc != 1 && !argv[0])
	{
		ft_putendl_fd("bash: error: no parameters allowed\n", 2);
		return (1);
	}
	ft_init(&data);
	data->env = env;
	data->hist = &hist;
	data->pl = &pl;
	ft_set_term(1);
	ft_shell_prompt();
	ft_input(data);
	return(0);
}
