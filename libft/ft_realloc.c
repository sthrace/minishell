#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*newptr;

    if (!ptr)
        return (NULL);
    newptr = malloc(size);
    if (newptr == NULL)
    {
        free(ptr);
        return (NULL);
    }
    ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}