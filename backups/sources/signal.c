#include "minishell.h"

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		write(2, "\033[1;34mminishell-> \033[0m", 23);
	}
}