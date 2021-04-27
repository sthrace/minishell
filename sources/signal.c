#include "minishell.h"

void    ft_free_array(char **array)
{
    int cnt;

    cnt = 0;
    if (!array)
        return ;
    while (array[cnt])
    {
        free(array[cnt]);
        cnt++;
    }
    free(array);
}

void    ft_free_str(char *str)
{
    free(str);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		write(2, "\033[1;34mminishell-> \033[0m", 23);
	}
}