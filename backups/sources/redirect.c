#include "minishell.h"

void    ft_close_fd(t_data *data, int type)
{
    if (type == 0 || type == 2)
    {
        if (data->cmds->fd0 != 0)
        {
            close(data->cmds->fd0);
            data->cmds->fd0 = 0;
        }
    }
    if (type == 1 || type == 2)
    {
        if (data->cmds->fd1 != 1)
        {
            close(data->cmds->fd1);
            data->cmds->fd1 = 1;
        }
    }
}

void    ft_clear_cmd(t_data *data, char *cmd, int start)
{
    if (data->cmds->rwrite == 2)
    {
        data->len += 2;
        start -= 2;
    }
    else
    {
        data->len += 1;
        start -= 1;
    }
    while (data->len--)
    {
        cmd[start] = 32;
        start++;
    }
    data->cmds->rread = 0;
    data->cmds->rwrite = 0;
}

void    ft_set_fd(t_data *data, char *cmd, int start)
{
    char *file;

    file = NULL;
    if (data->cmds->fdnum == 0)
        file = ft_substr(cmd, start, data->len);
    if (file)
    {
        if (data->cmds->rwrite == 1)
            data->cmds->fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
        else if (data->cmds->rwrite == 2)
            data->cmds->fd1 = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
        else if (data->cmds->rread == 1)
            data->cmds->fd0 = open(file, O_RDONLY);
        free(file);    
    }
}

void    ft_select_source(t_data *data, char *cmd, int *i, int start)
{
    data->len = 0;
    if (data->cmds->rread == 1 || data->cmds->rwrite > 0)
        cmd[*i] = 32;
    if (data->cmds->rwrite == 2)
        cmd[*i + 1] = 32;
    while (cmd[*i] == 32 && cmd[*i + 1] != 0)
        *i += 1;
    start = *i;
    while (cmd[*i] != 32 && cmd[*i] != 62 && cmd[*i] != 60 && cmd[*i] != 0)
    {
        if (cmd[*i] == 38)
        {
            data->cmds->fdnum = 1;
            data->cmds->fd1 = ft_atoi(&cmd[*i + 1]);
        }
        *i += 1;
        data->len++;
    }
    ft_set_fd(data, cmd, start);
    ft_clear_cmd(data, cmd, start);
    if (cmd[*i] == 0 || cmd[*i] == 62 || cmd[*i] == 60)
        *i -= 1;
}

void    ft_check_redirect(t_data *data, char *cmd, int i)
{
    ft_reset_flags(data, 1, 0);
    ft_close_fd(data, 2);
    while (cmd[++i])
    {   
        ft_flagswitch(data, cmd[i], 0);
        if (cmd[i] == 62 && !data->quotes)
        {
            ft_close_fd(data, 1);
            data->cmds->rwrite++;
            if (cmd[i + 1] && cmd[i + 1] == 62)
                data->cmds->rwrite++;
            ft_select_source(data, cmd, &i, 0);
        }
        else if (cmd[i] == 60 && !data->quotes)
        {
            ft_close_fd(data, 0);
            data->cmds->rread = 1;
            ft_select_source(data, cmd, &i, 0);
        }
    }
}