#include "minishell.h"

t_list	*envp_to_lst(char *envp[])
{
	int		i;
	t_list	*begin;

	if (!envp)
		return (0);
	i = 0;
	begin = 0;
	while (envp[i])
	{
		if (set_var(&begin, envp[i], ft_lstsize(begin)))
			return (0);
		i++;
	}
	return (begin);
}

char	**env_to_arr(t_list *env)
{
	char	**arr;
	char	*str;

	arr = 0;
	while (env)
	{
		if (((t_var *)(env->content))->value == 0)
		{
			env = env->next;
			continue ;
		}
		str = ft_strjoin(((t_var *)env->content)->key, "=");
		ft_arradd(&arr, ft_strjoin(str, ((t_var *)env->content)->value));
		free(str);
		env = env->next;
	}
	return (arr);
}

void	print_env(t_list *env)
{
	while (env)
	{
		if (((t_var *)(env->content))->value == 0)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(((t_var *)(env->content))->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_var *)(env->content))->value, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

void	print_export(t_list *env)
{
	char	**envp;
	char	*value;
	t_list	*temp;
	int		i;

	envp = 0;
	temp = env;
	while (temp)
	{
		ft_arradd(&envp, ((t_var *)temp->content)->key);
		temp = temp->next;
	}
	ft_arrsort(&envp);
	i = 0;
	while (envp[i])
	{
		value = get_var(env, envp[i]);
		if (value)
			printf("declare -x %s=\"%s\"\n", envp[i], value);
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
	ft_arrclear(envp);
}
