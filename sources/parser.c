#include "minishell.h"

// static void  ft_execute(char **argv, char *file)
// {
//     extern char **environ;
//     pid_t pid;
//     int timer;
    
//     pid = fork();
//     if (!pid)
//     {
//         if ((execve(file, argv, environ)) && errno == EACCES)
//         {
//             timer = 1;
//             printf("%s\n", strerror(errno));
//         }
//     }
//     free(file);
//     wait(&timer);
//     kill (pid, 1);
// }

// static char *ft_binsearch(char **argv)
// {
//     char        **paths;
//     char        *file;
//     int         cnt;
//     struct stat buf[4096];
//     char        *dir;

//     cnt = 0;
//     if (!getenv("PATH"))
//     {
//         printf("bash: %s\n", strerror(errno));
//         return (0x0);
//     }
//     else if (argv[0][0] != '.')
//     {
//         paths = ft_split(getenv("PATH"), ':');
//         cnt = -1;
//         while (paths[++cnt])
//         {
//             dir = ft_strjoin(paths[cnt], "/");
//             file = ft_strjoin(dir, argv[0]);
//             free(dir);
//             free(paths[cnt]);
//             if (!stat(file, buf))
//                 break ;
//             file = NULL;
//             free(file);
//         }
//         free(paths);
//     }
//     else
//         file = ft_strdup(argv[0]);
//     return (file);
// }

static void ft_sorter(t_data *data, int argc, char **argv)
{
    if (!(ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "ECHO", ft_strlen(argv[0]))))
        ft_echo(argc, argv);
    else if (!(ft_strncmp(argv[0], "cd", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "CD", ft_strlen(argv[0]))))
        ft_cd(argc, argv);
    else if (!(ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))) || !(ft_strncmp(argv[0], "PWD", ft_strlen(argv[0]))))
        ft_pwd();
    // else if (!(ft_strncmp(argv[0], "export", ft_strlen(argv[0]))))
    //     ft_export(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "unset", ft_strlen(argv[0]))))
    //     ft_unset(data, argc, argv);
    // else if (!(ft_strncmp(argv[0], "env", ft_strlen(argv[0]))))
    //     ft_env(data, argc, argv);
    else if (!(ft_strncmp(argv[0], "exit", ft_strlen(argv[0]))))
        ft_exit(data, argc, argv);
    else
        ft_execute(argv, ft_binsearch(argv));
}

void    ft_parser(t_data *data)
{
    int     i;
    char    **argv;

    i = -1;
    argv = (char **)malloc(sizeof(char *) * data->command->argc + 1);
    if (argv == NULL)
        ft_init(&data);
    while (++i < data->command->argc)
    {
        data->command->type[i] = data->command->argv[i][0];
        if (data->command->type[i] != 39 && data->command->type[i] != 34)
            data->command->type[i] = 1;
        if (data->command->type[i] == 39 || data->command->type[i] == 34)
            argv[i] = ft_substr(data->command->argv[i], 1, ft_strlen(data->command->argv[i]) - 2);
        else
            argv[i] = ft_strdup(data->command->argv[i]);
        free(data->command->argv[i]);
        if ((data->command->type[i] == 1 || data->command->type[i] == 34) && ft_strchr(argv[i], '$'))
            argv[i] = ft_insert_env(argv[i], -1, 0);
    }
    ft_sorter(data, data->command->argc, argv);
}