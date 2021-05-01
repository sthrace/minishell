#include "minishell.h"

static void  ft_execute(t_data *data, char **argv, char *file)
{
    extern char **environ;
    int i;

    i = -1;
    if (!fork())
    {
        if (data->cmds->fd0 > 0)
            dup2(data->cmds->fd0, 0);
        if (data->cmds->fd1 > 1)
            dup2(data->cmds->fd1, 1);
        data->ret = execve(file, argv, environ);
        if (data->ret && errno == EACCES)
            printf("bash: %s: command not found\n", file);
        exit(data->ret);
    }
    while ((wait(&data->ret)) != -1 || errno != ECHILD)
        ;
    data->ret /= 256;
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

void ft_binsearch(t_data *data, char **argv, int cnt, char *dir)
{
    char        **paths;
    char        *file;
    struct stat buf[4096];

    paths = ft_split_path();
    if (argv[0][0] == 46 || argv[0][0] == 47)
        ft_execute(data, argv, ft_strdup(argv[0]));
    else
    {
        while (paths[++cnt])
        {
            dir = ft_strjoin(paths[cnt], "/");
            file = ft_strjoin(dir, argv[0]);
            free(dir);
            data->ret = stat(file, buf);
            if (!data->ret)
                break ;
            free(file);
        }
        if (data->ret == -1)
            printf("bash: %s: command not found\n", argv[0]);
        ft_free_array(paths);
        if (data->ret != -1)
            ft_execute(data, argv, file);
    }
}

void ft_sorter(t_data *data, int argc, char **argv)
{
    if ((!(ft_strncmp(argv[0], "echo", 4)) || !(ft_strncmp(argv[0], "ECHO", 4))) && ft_strlen(argv[0]) == 4)
        ft_echo(data, argc, argv);
    else if ((!(ft_strncmp(argv[0], "cd", 2)) || !(ft_strncmp(argv[0], "CD", 2))) && ft_strlen(argv[0]) == 2)
        ft_cd(argc, argv);
    else if ((!(ft_strncmp(argv[0], "pwd", 3)) || !(ft_strncmp(argv[0], "PWD", 3))) && ft_strlen(argv[0]) == 3)
        ft_pwd();
    // else if (!(ft_strncmp(argv[0], "export", ft_strlen(argv[0]))))
    //     ft_export(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "unset", ft_strlen(argv[0]))))
    //     ft_unset(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "env", ft_strlen(argv[0]))))
    //     ft_env(data, argc, argv);
    else if ((!(ft_strncmp(argv[0], "exit", 4)) || !(ft_strncmp(argv[0], "EXIT", 4))) && ft_strlen(argv[0]) == 4)
        ft_exit(data, argc, argv, -1);
    else
        ft_binsearch(data, argv, -1, NULL);
    free(data->cmds);
}