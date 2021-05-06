#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <ncurses.h>
# include <term.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>

#define STDIN	0
#define STDOUT	1
#define RD	0
#define WR	1

typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

typedef struct s_hist
{
	char	*file;
	int		size;
	int		pos;
	char	**cmds;
}				t_hist;

typedef struct	s_pl
{
	int fdin[2];
	int fdout[2];
	int pids[100];
	int state;
	int count;
}				t_pl;

typedef struct s_flags
{
    int     length;
    int     begin;
    int     start;
    int     swap;
    int     res;
    int     quotes;
    int     dquote;
    int     squote;
    int     omit;
    int     esc;
    int     fdread;
    int     fdwrite;
    int     fdamp;
    char    *key;
}               t_flags;

typedef struct s_data
{
    char    *line;
    char    *cmd;
    char    **argv;
    int     argc;
    int     fd0;
    int     fd1;
    int     ret;
    int     len;
    t_flags flg;
	t_hist	*hist;
	t_list	*env;
	t_pl	*pl;
}               t_data;

int         g_sig;

// parser.c //

void        ft_parser(t_data *data, int x);

// term.c //

void    ft_set_term(int option);
void    ft_termios(t_data *data, char *str, int len);

// lexer.c //

void    ft_line(t_data *data, char *str, int len);
void	ft_get_cmd(t_data *data, int i);

// validator.c //

void	ft_validate_line(t_data *data, int i);
void    ft_flags(t_data *data, char c, int type);

// redirect.c //

void    ft_check_redirects(t_data *data, int i);

// signal.c //

void	sig_handler(int sig);
void	child_sig_handler(int sig);

// execute.c //

void    ft_sorter(t_data *data);

// builtins.c //

void ft_pwd(void);
void	ft_cd(t_data *data, int ret, char *pwd, char *oldpwd);
void ft_echo(t_data *data);
void ft_exit(t_data *data, int i);

// utils.c //

void ft_free_array(char **array);
void    ft_line_handler(t_data *data, char *str, int len, int type);
void	ft_pointer_inc(int *a, int *b);
void	ft_str_handle(t_data *data, char **insert, char **env);
void	ft_set_argv(t_data *data, int x, char **insert);

// env.c //

t_list	*envp_to_lst(char *envp[]);
void	print_env(t_list *env);
void	print_export(t_list *env);
char	*get_var(t_list *env, char *str);
int 	set_var(t_list **begin, char *str, int n);
int		unset_var(t_list **begin, char *str);

// history.c //

int		init_hist(t_hist *hist);
int		read_file(char *file, char ***arr);
int		write_str(char *file, char *str, int mode);
int		add_hist(t_hist *hist, char *str);

// minishell.c //

void    ft_init(t_data **data);
void	ft_shell_prompt();

#endif