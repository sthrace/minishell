#include "minishell.h"

void	ft_flags(t_data *data, char c, int type)
{
	if (type == 0)
	{
		data->flg.esc = 0;
		data->flg.quotes = 0;
		data->flg.fdread = 0;
		data->flg.fdwrite = 0;
	}
	if (type == 1 || type == 2)
	{
		if (c == 92 && (!data->flg.esc || data->flg.esc == 1))
			data->flg.esc = 2;
		else if (data->flg.esc == 2)
			data->flg.esc = 1;
		else
			data->flg.esc = 0;
	}
	if (type == 1)
	{
		if (!data->flg.esc && (c == 34 || c == 39) && !data->flg.quotes)
			data->flg.quotes = c;
		else if (!data->flg.esc && data->flg.quotes && c == \
			data->flg.quotes)
			data->flg.quotes = 0;
	}
}

static void	ft_validate_dups(t_data *data, int i)
{
	while (data->line[++i])
	{
		ft_flags(data, data->line[i], 2);
		if ((!data->flg.esc && (data->line[i] == ';' || data->line[i] == '|' || data->line[i] \
		== '<') && data->line[i + 1] == data->line[i]) || (data->line[i] == '>' && data->\
		line[i + 1] == data->line[i] && data->line[i + 2] == data->line[i]))
		{
			if (data->line[i] != 62)
				printf("bash: syntax error near unexpected token `%c%c'\n", \
				data->line[i], data->line[i]);
			else
				printf("bash: syntax error near unexpected token `%c'\n", \
				data->line[i]);
			data->ret = 258;
			ft_init(&data);
			return ;
		}
		if (data->line[data->len - 2] == 92)
		{
			write(2, "bash: >\n", 8);
			ft_init(&data);
			return ;
		}
	}
	ft_get_cmd(data, -1);
}

static void	ft_validate_quotes(t_data *data, int i)
{
	ft_flags(data, '\0', 0);
	while (data->line[++i])
		ft_flags(data, data->line[i], 1);
	if (data->flg.quotes)
	{
		write(2, "bash: >\n", 8);
		ft_init(&data);
		return ;
	}
	ft_validate_dups(data, -1);
}

void	ft_validate_line(t_data *data, int i)
{
	data->line[data->len - 1] = 0;
	ft_set_term(2);
	add_hist(data->hist, data->line);
	if (data->line[0] == 0 && data->len == 1)
	{
		ft_init(&data);
		return ;
	}
	while (data->line[++i])
	{
		while (data->line[i] == 32)
			i++;
		if (data->line[i] == ';')
		{
			if (data->line[i + 1] == ';')
				write(2, "bash: syntax error near unexpected token `;;'\n", 46);
			else
				write(2, "bash: syntax error near unexpected token `;'\n", 45);
			ft_init(&data);
			data->ret = 258;
			return ;
		}
		break ;
	}
	ft_validate_quotes(data, -1);
}
