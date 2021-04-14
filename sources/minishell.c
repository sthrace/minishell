#include "minishell.h"

void ft_line(t_shell *shell, char *str, int len)
{
	if (!shell->line)
	{
		shell->line = (char *)malloc(sizeof(char) * 2);
		shell->line[0] = str[0];
		shell->line[1] = '\0';
		shell->linelen = len;
	}
	else
	{
		shell->linelen += len;
		if (shell->linelen > 0)
		{
			shell->line = (char *)ft_realloc(shell->line, (sizeof(char) * (shell->linelen + 1)));
			if (len > 0)
				shell->line[shell->linelen - 1] = str[0];
			shell->line[shell->linelen] = '\0';
		}
		else
		{
			free(shell->line);
			shell->line = NULL;
		}
	}
}

void ft_init(t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(0);
	}
	(*shell)->line = NULL;
}

void ft_initterm(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~ECHO;			// отключаем вывод служебных символов
	term->c_lflag &= ~ICANON;		// переходим в неканонический посимвольный режим ввода
	tcsetattr(0, TCSANOW,  term);	// применяем настройки
	tgetent(0, getenv("TERM"));	// загружаем базу данных текущего терминала
	tputs(save_cursor, 1, &ft_putchar);
}

void	ft_termios(t_shell *shell, char *str, int len)
{
	if (!ft_strncmp(str, "\e[A", len))
	{
		tputs(restore_cursor, 1, &ft_putchar);
		tputs(delete_line, 1, ft_putchar);
		ft_putstr_fd("previous", 1);
	}
	else if (!ft_strncmp(str, "\e[B", len))
	{
		tputs(restore_cursor, 1, &ft_putchar);
			tputs(delete_line, 1, ft_putchar);
			ft_putstr_fd("next", 1);
	}
	else if (!ft_strncmp(str, "\177", len))
	{
		if (shell->linelen > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			ft_line(shell, str, -1);
		}
	}
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
	while (ft_strcmp(str, "\n"))
	{
		len = read(0, str, 3);
		if (str[0] == '\e' || !ft_strncmp(str, "\177", len))
			ft_termios(shell, str, len);
		else if (!ft_strncmp(str, "\4", len))
			break ;
		else
		{
			write(1, str, len);
			ft_line(shell, str, len);
		}
	}
	printf("Str: %s\n", shell->line);
	return(0);
}
