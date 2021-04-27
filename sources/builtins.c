#include "minishell.h"

void ft_pwd(void)
{
    char    buf[4096];

    printf("%s\n", getcwd(buf, 4096));
}

void ft_cd(int argc, char **argv)
{
    int i;
    char *newdir;
    int ret;

    newdir = ft_strdup("");
    if (argc == 2)
        newdir = ft_strjoin(newdir, argv[1]);
    else if (argc > 2)
    {
        i = 0;
        while (++i < argc)
            newdir = ft_strjoin(newdir, argv[i]);
    }
    else
        printf("\n");
    ret = chdir(newdir);
    if (ret == -1)
        printf("bash: cd: %s: %s\n", newdir, strerror(errno));
}

void ft_echo(int argc, char **argv)
{
    int i;
    int n;

    i = 0;
    n = 0;
    if (argc > 1 && (!(ft_strncmp(argv[1], "-n", ft_strlen(argv[1])))))
        n = 1;
    while (++i < argc)
    {
        if (n)
            i++;
        write(1, argv[i], (int)ft_strlen(argv[i]));
    }
    if (!n)
        write(1, "\n", 1);
}

void ft_exit(t_data *data, int argc, char **argv, int i)
{
    if (argc > 1)
    {
        while (argv[1][++i])
        {
            if (!(ft_isdigit(argv[1][i])))
            {
                data->ret = 2;
                printf("exit\nbash: exit: %s: numeric argument required\n", argv[1]);
            }
        }
    }
    if (argc > 2 && data->ret != 2)
    {
        data->ret = 1;
        printf("exit\nbash: exit: too many arguments\n");
    }
    if (data->ret != 2)
    {
        if (argc > 1)
            data->ret = ft_atoi(argv[1]);
        printf("exit\n");
    }
    exit(data->ret);
}