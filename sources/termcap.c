#include "minishell.h"

void	ft_set_term(int option)
{
	struct termios	term;

	if (option == 1)
	{
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHO;
		term.c_lflag &= ~ICANON;
		term.c_cc[VEOF] = 4;
		tcsetattr(0, TCSANOW, &term);
		tgetent(0, getenv("TERM"));
		tputs(save_cursor, 1, &ft_putchar);
	}
	if (option == 2)
	{
		tcgetattr(0, &term);
		term.c_lflag |= ECHO;
		term.c_lflag |= ICANON;
		tcsetattr(0, TCSANOW, &term);
	}
}

static void	term_key_up(t_data *data)
{
	tputs(restore_cursor, 1, &ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_shell_prompt();
	ft_putstr_fd(data->hist->cmds[--(data->hist->pos)], 1);
	free(data->line);
	data->line = NULL;
	data->line = ft_strdup(data->hist->cmds[data->hist->pos]);
	data->len = ft_strlen(data->hist->cmds[data->hist->pos]);
}

static void	term_key_down(t_data *data)
{
	tputs(restore_cursor, 1, &ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_shell_prompt();
	if (data->hist->pos < data->hist->size)
		ft_putstr_fd(data->hist->cmds[++(data->hist->pos)], 1);
	free(data->line);
	data->line = NULL;
	data->line = ft_strdup(data->hist->cmds[data->hist->pos]);
	data->len = ft_strlen(data->hist->cmds[data->hist->pos]);
}

void	ft_termios(t_data *data, char *str, int len)
{
	if (!ft_strncmp(str, "\e[A", len))
	{
		if (data->hist->pos <= 0)
			return ;
		term_key_up(data);
	}
	else if (!ft_strncmp(str, "\e[B", len))
		term_key_down(data);
	else if (!ft_strncmp(str, "\177", len))
	{
		if (data->len > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			ft_line(data, str, -1);
		}
	}
}
