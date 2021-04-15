#include "libft.h"

int     ft_metachar(int c)
{
    if (c == 59 || c == 39 || c == 34 || c == 60 || c == 62 || c == 124 || c == 36)
        return (1);
    return (0);
}