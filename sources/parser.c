#include "minishell.h"

static void ft_insert_env(char *line)
{
    char    *ptr;

    printf("Here we will search for dollar sign: %s\n", line);
    ptr = ft_strchr(line, '$');
    printf("Dollar sign at: %p\n", ptr);
}

void    ft_parser(t_data *data)
{
    int     i;
    char    **argv;

    i = 0;
    argv = (char **)malloc(sizeof(char *) * data->command->argc + 1);
    if (argv == NULL)
        ft_init(&data);
    printf("New pointer at: %p\n", argv);
    while (i < data->command->argc)
    {
        printf("cycle start with i: %d and argc: %d\n", i, data->command->argc);
        data->command->type[i] = data->command->argv[i][0];
        if (data->command->type[i] != 39 && data->command->type[i] != 34)
            data->command->type[i] = 1;
        if (data->command->type[i] == 39 || data->command->type[i] == 34)
            argv[i] = ft_substr(data->command->argv[i], 1, ft_strlen(argv[i]) - 2);
        else
            argv[i] = ft_strdup(data->command->argv[i]);
        free(data->command->argv[i]);
        printf("Clean off quotes: %s\n", argv[i]);
        if (data->command->type[i] == 1 || data->command->type[i] == 34)
            ft_insert_env(argv[i]);
        i++;
    }
    printf("cycle end");
    argv[i] = NULL;
}