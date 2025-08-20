#include "../minishell.h"

void	ft_add_key(char *key)
{
	t_env	*var;

	var = check_key(key);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup("");
	}
	else
	{
		var = ft_lstnew_env(ft_strdup(key), ft_strdup(""));
		ft_lstadd_back_env(&g_all_data->env_list, var);
	}
}

void	ft_add_key2(char *key)
{
	t_env	*var;

	var = check_key(key);
	if (var)
		return ;
	else
	{
		var = ft_lstnew_env(ft_strdup(key), NULL);
		ft_lstadd_back_env(&g_all_data->env_list, var);
	}
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
		{
			ft_dprintf(1, "declare -x %s=", env->key);
			ft_dprintf(1, "\"%s\"\n", env->value);
		}
		else
			ft_dprintf(1, "declare -x %s\n", env->key);
		env = env->next;
	}
}
