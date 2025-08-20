#include "../minishell.h"

void	env_i(t_env **our_env)
{
	t_env	*node;
	char	buffer[PATH_MAX];

	node = ft_lstnew_env(ft_strdup("PWD"), ft_strdup(getcwd(buffer,
					sizeof(buffer))));
	ft_lstadd_back_env(our_env, node);
	node = ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"));
	ft_lstadd_back_env(our_env, node);
	node = ft_lstnew_env(ft_strdup("_"), ft_strdup("./minishell"));
	ft_lstadd_back_env(our_env, node);
}

void	get_env(char **env, t_env **our_env)
{
	int		i;
	t_env	*node;
	char	**key_val;

	if (env && !*env)
		env_i(our_env);
	else
	{
		i = 0;
		while (env && env[i])
		{
			key_val = ft_split(env[i], '=');
			node = ft_lstnew_env(ft_strdup(key_val[0]), ft_strdup(key_val[1]));
			ft_lstadd_back_env(our_env, node);
			ft_free(key_val);
			i++;
		}
	}
}
