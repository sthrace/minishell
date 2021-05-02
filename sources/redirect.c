#include "minishell.h"

void    ft_close_fd(t_data *data, int type)
{
    if (type == 0 || type == 2)
    {
        if (data->fd0 != 0)
        {
            close(data->fd0);
            data->fd0 = 0;
        }
    }
    if (type == 1 || type == 2)
    {
        if (data->fd1 != 1)
        {
            close(data->fd1);
            data->fd1 = 1;
        }
    }
}

void    ft_clear_cmd(t_data *data)
{
    while (data->flg.length--)
    {
        data->cmd[data->flg.begin] = 32;
        data->flg.begin++;
    }
    data->flg.fdread = 0;
    data->flg.fdwrite = 0;
}

void    ft_set_fd(t_data *data)
{
    char *file;

    file = NULL;
    if (data->flg.fdamp == 0)
        file = ft_substr(data->cmd, data->flg.begin, data->flg.length);
    if (file)
    {
        if (data->flg.fdwrite == 1)
            data->fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
        else if (data->flg.fdwrite == 2)
            data->fd1 = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
        else if (data->flg.fdread == 1)
            data->fd0 = open(file, O_RDONLY);
        if (data->fd0 == -1 || data->fd1 == -1)
        {
            printf("bash: syntax error near unexpected token `newline'");
            return ;
        }
        free(file);    
    }
}

void    ft_select_source(t_data *data, int *i)
{
    data->flg.length = 0;
    data->flg.fdamp = 0;
    if (data->flg.fdread == 1 || data->flg.fdwrite > 0)
        data->cmd[*i] = 32;
    if (data->flg.fdwrite == 2)
        data->cmd[*i + 1] = 32;
    while (data->cmd[*i] == 32)
        *i += 1;
    data->flg.begin = *i;
    while (data->cmd[*i] != 32 && data->cmd[*i] != 62 && data->cmd[*i] != 60 && data->cmd[*i])
    {
        if (data->cmd[*i] == 38)
        {
            data->flg.fdamp = 1;
            data->fd1 = ft_atoi(&data->cmd[*i + 1]);
        }
        *i += 1;
        data->flg.length++;
    }
    ft_set_fd(data);
    ft_clear_cmd(data);
    if (data->cmd[*i] == 0 || data->cmd[*i] == 62 || data->cmd[*i] == 60)
        *i -= 1;
}

void    ft_check_redirects(t_data *data, int i)
{
    ft_flags(data, '\0', 0);
    ft_close_fd(data, 2);
    data->flg.begin = 0;
    while (data->cmd[++i])
    {   
        ft_flags(data, data->cmd[i], 1);
        if (data->cmd[i] == 62 && !data->flg.quotes && !data->flg.esc)
        {
            ft_close_fd(data, 1);
            data->flg.fdwrite++;
            if (data->cmd[i + 1] == 62)
                data->flg.fdwrite++;
            ft_select_source(data, &i);
        }
        else if (data->cmd[i] == 60 && !data->flg.quotes && !data->flg.esc)
        {
            ft_close_fd(data, 0);
            data->flg.fdread = 1;
            ft_select_source(data, &i);
        }
    }
}