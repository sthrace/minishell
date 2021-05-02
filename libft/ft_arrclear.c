#include "libft.h"

int	ft_arrclear(char **arr)
{
	unsigned int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}