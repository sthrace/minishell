#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*newptr;

    newptr = malloc(size);
    if (newptr == NULL)
    {
        if (ptr)
            free(ptr);
        return (NULL);
    }
    if (ptr)
    {
        ft_memcpy(newptr, ptr, size);
	    free(ptr);
    }
	return (newptr);
}