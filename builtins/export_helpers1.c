#include "../minishell.h"

char	*get_value(char *buffer, int i)
{
	char	*value;

	value = NULL;
	while (buffer[i])
	{
		value = ft_joiner(value, buffer[i]);
		i++;
	}
	return (value);
}

t_env	*check_key(char *key)
{
	t_env	*env;

	env = g_all_data->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_concat_var(char *key, char *value)
{
	t_env	*var;
	char	*tmp_value;

	var = check_key(key);
	if (var)
	{
		tmp_value = var->value;
		var->value = ft_strjoin(tmp_value, value);
		free(tmp_value);
	}
	else
	{
		var = ft_lstnew_env(ft_strdup(key), ft_strdup(value));
		ft_lstadd_back_env(&g_all_data->env_list, var);
	}
}

void	ft_add_env_var(char *key, char *value)
{
	t_env	*var;

	var = check_key(key);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
	else
	{
		var = ft_lstnew_env(ft_strdup(key), ft_strdup(value));
		ft_lstadd_back_env(&g_all_data->env_list, var);
	}
}
