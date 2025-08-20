#include "../minishell.h"

void	ft_sort_env(t_env *env)
{
	int		swapped;
	t_env	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp = env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				ft_swap_export(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
	}
	tmp = env;
	print_export(tmp);
}

void	print_env(int fd)
{
	t_env	*env;

	env = g_all_data->env_list;
	while (env)
	{
		if (env->key && env->value)
		{
			ft_dprintf(fd, "%s=", env->key);
			ft_dprintf(fd, "%s\n", env->value);
		}
		env = env->next;
	}
}

int	ft_check_slash(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		if (str[len - 1] == '/')
			return (1);
	}
	return (0);
}
