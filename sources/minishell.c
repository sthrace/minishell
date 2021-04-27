#include "minishell.h"

void ft_init(t_data **data)
{
	if (!(*(data)))
		*data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	(*data)->line = NULL;
	(*data)->cmds = NULL;
	(*data)->ret = 0;
	signal(SIGINT, ft_sig_handler);
}

void	ft_shell_prompt()
{
	write(2, "\033[1;34mminishell-> \033[0m", 23);
}

static void	ft_input(t_data *data)
{
	char	str[3];
	int		len;

	ft_shell_prompt();
	while (1)
	{	
		signal(SIGINT, ft_sig_handler);
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
			ft_splitcmd(data, data->line, -1, 0);
			ft_shell_prompt();
		}
		if (str[0] == '\4')
			break ;
	}
}

int	main(int argc, char **argv)
{
	struct	termios term;
	t_data	*data;

	if (argc != 1 && !argv[0])
		return (1);
	ft_init(&data);
	ft_initterm(&term);
	//ft_term(1);
	ft_input(data);
	return(0);
}
