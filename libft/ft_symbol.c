#include "libft.h"

int     ft_symbol(int c)
{
    if (c == 33 || c == 35 || c == 37 || c == 38 || c == 40 || c == 41 || (c >= 43 && c <=47)
    || c == 58 || c == 61 || c == 64 || (c >= 91 && c <=96) || c == 123 || c == 125 || c == 126)
        return (1);
    return (0);
}