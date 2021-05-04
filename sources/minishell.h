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

typedef struct s_flags
{
    int     length;
    int     begin;
    int     start;
    int     swap;
    int     res;
    int     quotes;
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
    int     history;
    t_flags flg;
	t_hist	*hist;
	t_list	*env;
}               t_data;

// parser.c //

void        ft_parser(t_data *data, int x);

// parser_utils.c //

void ft_set_prefix(t_data *data, int x, char **prefix);
int  ft_substitute_env(t_data *data, int x, int *i, char **insert);
void ft_join_all(char **temp, char **prefix, char **insert, char **output);
void ft_finalize(t_data *data, char **output, char **temp, int x);

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

// execute.c //

void    ft_sorter(t_data *data);

// builtins.c //

void ft_pwd(void);
void ft_cd(t_data *data);
void ft_echo(t_data *data);
void ft_exit(t_data *data, int i);

// utils.c //

void ft_free_array(char **array);

// env.c //

t_list	*envp_to_lst(char *envp[]);
void	print_env(t_list *env);
void	print_export(t_list *env);
char	*get_var(t_list *env, char *str);
int 	set_var(t_list **begin, char *str, int n);
int		unset_var(t_list **begin, char *str);

// history.c //
int		read_file(char *file, char ***arr);
int		write_str(char *file, char *str, int mode);
int		add_hist(t_hist *hist, char *str);

// minishell.c //

void    ft_init(t_data **data);
void	ft_shell_prompt();

#endif