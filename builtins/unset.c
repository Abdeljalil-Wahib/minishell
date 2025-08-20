#include "../minishell.h"

int	get_key_pos(char *key)
{
	t_env	*env;
	int		i;

	env = g_all_data->env_list;
	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (-1);
}

void	ft_unset_first(void)
{
	t_env	*to_be_unset;

	to_be_unset = g_all_data->env_list;
	g_all_data->env_list = g_all_data->env_list->next;
	free(to_be_unset->key);
	free(to_be_unset->value);
	free(to_be_unset);
	return ;
}

void	ft_unset_mid(char *key)
{
	t_env	*to_be_unset;
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = g_all_data->env_list;
	to_be_unset = env;
	while (to_be_unset && ft_strcmp(to_be_unset->key, key) != 0)
	{
		prev = to_be_unset;
		to_be_unset = to_be_unset->next;
	}
	prev->next = to_be_unset->next;
	free(to_be_unset->key);
	free(to_be_unset->value);
	free(to_be_unset);
}

void	ft_unset_last(void)
{
	t_env	*second_to_last;
	t_env	*to_be_unset;
	t_env	*env;

	env = g_all_data->env_list;
	to_be_unset = ft_lstlast_env(env);
	second_to_last = env;
	while (second_to_last && second_to_last->next->next)
		second_to_last = second_to_last->next;
	free(to_be_unset->key);
	free(to_be_unset->value);
	free(to_be_unset);
	second_to_last->next = NULL;
}

void	ft_unset(t_commands *commands)
{
	int		size;
	int		i;
	t_env	*env;

	env = g_all_data->env_list;
	i = 1;
	while (commands->options[i])
	{
		if (ft_strcmp(commands->options[i], "_") != 0)
		{
			size = ft_lstsize_env(env);
			if (commands->options[i] && get_key_pos(commands->options[i]) == 0)
				ft_unset_first();
			else if (commands->options[i]
				&& get_key_pos(commands->options[i]) > 0
				&& get_key_pos(commands->options[i]) != size)
				ft_unset_mid(commands->options[i]);
			else
				ft_unset_last();
		}
		i++;
	}
}
