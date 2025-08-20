#include "../minishell.h"

int	ft_env_size(t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

char	**ft_convert_env(t_env *env_list)
{
	int		size;
	char	**env_arr;
	char	*line;
	char	*tmp;
	int		i;

	size = ft_env_size(env_list);
	env_arr = malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env_list)
	{
		tmp = ft_strjoin(env_list->key, "=");
		line = ft_strjoin(tmp, env_list->value);
		free(tmp);
		env_arr[i] = line;
		i++;
		env_list = env_list->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
