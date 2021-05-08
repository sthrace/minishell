#include "minishell.h"

char	*get_var(t_list *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->key, str))
			return (((t_var *)env->content)->value);
		env = env->next;
	}
	return (0);
}

int	add_var(t_list **begin, char **key_val, int n)
{
	t_list	*new;

	new = ft_lstnew(malloc(sizeof(t_var)));
	if (new == 0)
		return (3);
	((t_var *)(new->content))->key = key_val[0];
	((t_var *)(new->content))->value = key_val[1];
	ft_lstadd_at(begin, new, n);
	return (0);
}

int	set_var(t_list **begin, char *str, int n)
{
	t_list	*temp;
	char	*sep;
	char	*key_val[2];

	sep = ft_strchr(str, '=');
	if (sep == str)
		return (printf("bash: export: `%s': not a valid identifier\n", str));
	if (sep != 0)
		*sep = '\0';
	if (sep != 0)
		sep++;
	key_val[0] = ft_strdup(str);
	key_val[1] = ft_strdup(sep);
	temp = *begin;
	while (temp)
	{
		if (!ft_strcmp(((t_var *)temp->content)->key, key_val[0]))
		{
			free(((t_var *)(temp->content))->key);
			free(((t_var *)(temp->content))->value);
			((t_var *)(temp->content))->key = key_val[0];
			((t_var *)(temp->content))->value = key_val[1];
			return (0);
		}
		temp = temp->next;
	}
	return (add_var(begin, key_val, n));
}

int	unset_var(t_list **begin, char *str)
{
	t_list	*temp;
	t_list	*prev;

	prev = 0;
	temp = *begin;
	while (temp)
	{
		if (!ft_strcmp(((t_var *)temp->content)->key, str))
		{
			if (prev)
				prev->next = temp->next;
			else
				*begin = temp->next;
			free(((t_var *)(temp->content))->key);
			free(((t_var *)(temp->content))->value);
			free(temp->content);
			free(temp);
			return (0);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
