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

static char **ft_split_path(void)
{
   if (!getenv("PATH"))
    {
        printf("bash: %s\n", strerror(errno));
        return (0x0);
    }
    return(ft_split(getenv("PATH"), ':'));
}

char *ft_binsearch(char **argv)
{
    char        **paths;
    char        *file;
    int         cnt;
    struct stat buf[4096];
    char        *dir;

    cnt = -1;
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
    return (file);
}