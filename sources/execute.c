#include "minishell.h"

void  ft_execute(char **argv, char *file)
{
    extern char **environ;
    pid_t pid;
    int timer;
    
    pid = fork();
    if (!pid)
    {
        if ((execve(file, argv, environ)) && errno == EACCES)
        {
            timer = 1;
            printf("%s\n", strerror(errno));
        }
    }
    free(file);
    wait(&timer);
    kill (pid, 1);
}

char *ft_binsearch(char **argv)
{
    char        **paths;
    char        *file;
    int         cnt;
    struct stat buf[4096];
    char        *dir;

    cnt = 0;
    if (!getenv("PATH"))
    {
        printf("bash: %s\n", strerror(errno));
        return (0x0);
    }
    else if (argv[0][0] != '.')
    {
        paths = ft_split(getenv("PATH"), ':');
        cnt = -1;
        while (paths[++cnt])
        {
            dir = ft_strjoin(paths[cnt], "/");
            file = ft_strjoin(dir, argv[0]);
            free(dir);
            free(paths[cnt]);
            if (!stat(file, buf))
                break ;
            file = NULL;
            free(file);
        }
        free(paths);
    }
    else
        file = ft_strdup(argv[0]);
    return (file);
}