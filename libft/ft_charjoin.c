#include "libft.h"

char		*ft_charjoin(char *line, char c)
{
	char		*joined;
	int			i;

	i = 0;
	while (line[i])
		i++;
	joined = (char *)malloc(i + 2);
	i = 0;
	while (line[i])
	{
		joined[i] = line[i];
		i++;
	}
	joined[i] = c;
	joined[i + 1] = '\0';
	free(line);
	return (joined);
}