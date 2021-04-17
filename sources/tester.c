#include <stdlib.h>

typedef struct s_command
{
    int     cmd_cnt;
    char    *token;
}               t_command;

typedef struct s_shell
{
    char    *line;
    t_command   *cmd;
}               t_shell;


static void		ft_count_commands(t_shell *shell)
{
	int		i;

	i = 0;
	shell->cmd_cnt = 1;
	if (shell->cmd)
		free(shell->cmd);
	while (shell->line[i] != '\0')
	{
		if (shell->line[i] == ';')
		{
			if (shell->line[i + 1] == ';')
			{
				shell->cmd_cnt = 0;
				printf("parse error near `;;'\n");
				break ;
				// signal(SIGINT, signal_handler);
			}	
			else
				shell->cmd_cnt++;
		}	
		i++;
	}
	shell->cmd = (t_command *)malloc(sizeof(t_command) * shell->cmd_cnt);
	if (shell->cmd == NULL)
		printf("%s\n", strerror(errno));
}
int     main()
{
    t_shell shell;
    
    shell.line = "asd ; asd ; asd";
    ft_count_commands(&shell);
}