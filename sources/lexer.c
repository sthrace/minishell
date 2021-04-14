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