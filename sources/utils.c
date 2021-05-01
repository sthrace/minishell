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