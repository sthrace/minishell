#include "minishell.h"

static void  ft_execute(char **argv, char *file)
{
    extern char **environ;

    if (!fork())
    {
        if ((execve(file, argv, environ)) && errno == EACCES)
            printf("bash: %s: command not found\n", file);
    }
    else
    while ((wait(NULL)) != -1 || errno != ECHILD)
        ;
}

static char **ft_split_path(void)
{
    char **paths;

    if (!getenv("PATH"))
    {
        printf("bash: %s\n", strerror(errno));
        return (0x0);
    }
    paths = ft_split(getenv("PATH"), ':');
    if (!paths)
    {
        printf("bash: %s\n", strerror(errno));
        return (0x0);
    }
    return(paths);
}

void ft_binsearch(char **argv)
{
    char        **paths;
    char        *file;
    int         cnt;
    struct stat buf[4096];
    char        *dir;

    if (argv[0][0] != '.')
    {
        paths = ft_split_path();
        cnt = -1;
        while (paths[++cnt])
        {
            dir = ft_strjoin(paths[cnt], "/");
            file = ft_strjoin(dir, argv[0]);
            free(dir);
            if (!stat(file, buf))
                break ;
            free(file);
        }
        ft_free_array(paths);
    }
    else
        file = ft_strdup(argv[0]);
    ft_execute(argv, file);
}