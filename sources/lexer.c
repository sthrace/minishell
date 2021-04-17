#include "minishell.h"

static void	ft_tokensize(t_shell *shell, int i, int x, int y)
{
	int		len;

	while (x < shell->ccnt)
	{
		while (y < shell->cmd[i].tcnt)
		{
			len = 0;
			if (shell->line[i] == ' ' && i == 0)
				y++;
		}
		x++;
	}
}

void		ft_count_tokens(t_shell *shell, int i, int x)
{
	while (++i < shell->ccnt)
		shell->cmd[i].tcnt = 0;
	i = 0;
	while (shell->line[i] != '\0')
	{
		if(shell->line[i] == ';')
		{
			shell->cmd[x].token = (t_token *)malloc(sizeof(t_token) * shell->cmd[x].tcnt);
			x++;
		}
		if ((i == 0 && ft_istoken(shell->line[i])) ||
				(i != 0 && ft_istoken(shell->line[i]) 
				&& shell->line[i - 1] == ' ') || 
				(i != 0 && ft_istoken(shell->line[i]) && 
				(shell->line[i - 1] == ';' || shell->line[i + 1] == ';')))
			shell->cmd[x].tcnt++;
		i++;
	}
	ft_tokensize(shell, 0, 0, 0);
}

void		ft_count_commands(t_shell *shell, int i)
{
	shell->ccnt = 1;
	if (shell->cmd)
		free(shell->cmd);
	while (shell->line[i] != '\0')
	{
		if (shell->line[i] == ';')
		{
			if (shell->line[i + 1] == ';')
			{
				shell->ccnt = 0;
				shell->line = NULL;
				printf("parse error near `;;'\n");
				break ;
			}	
			else
				shell->ccnt++;
		}	
		i++;
	}
	shell->cmd = (t_command *)malloc(sizeof(t_command) * shell->ccnt);
	if (shell->cmd == NULL)
		printf("%s\n", strerror(errno));
}

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