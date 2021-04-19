#include "minishell.h"

void ft_initterm(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~ECHO;			// отключаем вывод служебных символов
	term->c_lflag &= ~ICANON;		// переходим в неканонический посимвольный режим ввода
	tcsetattr(0, TCSANOW,  term);	// применяем настройки
	tgetent(0, getenv("TERM"));	// загружаем базу данных текущего терминала
	// tputs(save_cursor, 1, &ft_putchar);
}

void	ft_termios(t_data *data, char *str, int len)
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
		if (data->linelen > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			ft_line(data, str, -1);
		}
	}
}