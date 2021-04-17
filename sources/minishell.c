#include "minishell.h"

static void	ft_init_env(char **envp)
{
	int	cnt;

	cnt = 0;
	while (envp[cnt] != NULL)
		cnt++;
	g_env = (char **)malloc(sizeof(char *) * cnt + 1);
	if (g_env == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	while (cnt-- > 0)
		g_env[cnt] = ft_strdup(envp[cnt]);
}

static void ft_init(t_shell **shell, char **envp)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	(*shell)->line = NULL;
	(*shell)->cmd = NULL;
	ft_init_env(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	str[3];				// буфер для посимвольного чтения (3 байта для эскейп последовательностей)
	int		len;
	struct	termios term;
	t_shell	*shell;

	if (argc != 1 && !argv[0])
		return (1);
	ft_init(&shell, envp);
	ft_initterm(&term);
	while (1)
	{
		len = read(0, str, 3);
		if (str[0] == '\e' || !ft_strncmp(str, "\177", len))
			ft_termios(shell, str, len);
		else
		{
			write(1, str, len);
			ft_line(shell, str, len);
		}
		if (str[0] == '\n')
		{
			ft_count_commands(shell, 0);
			ft_count_tokens(shell, -1, 0);
		}
		if (str[0] == '\4')
			break ;
	}
	return(0);
}
