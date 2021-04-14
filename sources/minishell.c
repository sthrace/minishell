#include "minishell.h"

static void ft_init(t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(0);
	}
	(*shell)->line = NULL;
}

int	main()
{
	char	str[3];				// буфер для разных символов (1 - анг, 2 - рус, 3 - стрелочки)
	int		len;
	struct	termios term;
	t_shell	*shell;

	ft_init(&shell);
	ft_initterm(&term);
	str[0] = '0';
	while (1)
	{
		len = read(0, str, 3);
		if (str[0] == '\e' || !ft_strncmp(str, "\177", len))
			ft_termios(shell, str, len);
		else
		{
			write(1, str, len);
			ft_line(shell, str, len);
		}
		if (str[0] == '\n')
			ft_parser(shell);
		if (str[0] == '\4')
			break ;
	}
	return(0);
}
