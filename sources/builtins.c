#include "minishell.h"

void ft_pwd(void)
{
    char    buf[4096];

    printf("%s\n", getcwd(buf, 4096));
}

void ft_cd(t_data *data)
{
    int i;
    char *newdir;
    int ret;

    newdir = ft_strdup("");
    if (data->argc == 2)
        newdir = ft_strjoin(newdir, data->argv[1]);
    else if (data->argc > 2)
    {
        i = 0;
        while (++i < data->argc)
            newdir = ft_strjoin(newdir, data->argv[i]);
    }
    else
        printf("\n");
    ret = chdir(newdir);
    if (ret == -1)
        printf("bash: cd: %s: %s\n", newdir, strerror(errno));
}

void ft_echo(t_data *data)
{
    int i;
    short n;

    i = 0;
    n = 0;
    if (data->argc > 1 && (!(ft_strncmp(data->argv[1], "-n", 2))))
        n = 1;
    while (++i < data->argc)
    {
        if (n)
            i++;
        write(data->fd1, data->argv[i], ft_strlen(data->argv[i]));
        write(data->fd1, " ", 1);
    }
    if (!n)
        write(data->fd1, "\n", 1);
}

void ft_exit(t_data *data, int i)
{
    if (data->argc > 1)
    {
        while (data->argv[1][++i])
        {
            if (!(ft_isdigit(data->argv[1][i])))
            {
                data->ret = 2;
                printf("exit\nbash: exit: %s: numeric argument required\n", data->argv[1]);
            }
        }
    }
    if (data->argc > 2 && data->ret != 2)
    {
        data->ret = 1;
        printf("exit\nbash: exit: too many arguments\n");
        return ;
    }
    if (data->ret != 2)
    {
        if (data->argc > 1)
            data->ret = ft_atoi(data->argv[1]);
        printf("exit\n");
    }
    exit(data->ret);
}