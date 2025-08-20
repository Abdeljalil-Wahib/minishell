#include "../minishell.h"

t_env	*ft_copy_list(t_env *env)
{
	t_env	*env_copy_head;
	t_env	*env_copy;

	env_copy_head = NULL;
	while (env)
	{
		if (env->value)
			env_copy = ft_lstnew_env(ft_strdup(env->key),
					ft_strdup(env->value));
		else
			env_copy = ft_lstnew_env(ft_strdup(env->key), NULL);
		ft_lstadd_back_env(&env_copy_head, env_copy);
		env = env->next;
	}
	return (env_copy_head);
}

void	handle_keys(char *key)
{
	int		start;
	int		end;
	char	*res;

	start = 0;
	end = 0;
	if (!ft_check_space(key))
	{
		get_key(key);
		return ;
	}
	if (process_key_segment(key, &start, &end) == 0)
	{
		res = ft_substr(key, start, end);
		get_key(res);
	}
}

void	process_export_vars(t_commands *command)
{
	int	i;

	i = 1;
	while (command->options && command->options[i])
	{
		handle_keys(command->options[i]);
		i++;
	}
}

void	ft_export(t_commands *command)
{
	t_env	*env_copy;

	if (ft_strlen_double(command->options) == 1)
	{
		env_copy = ft_copy_list(g_all_data->env_list);
		ft_sort_env(env_copy);
		ft_lstclear_env(&env_copy);
	}
	else
		process_export_vars(command);
}
