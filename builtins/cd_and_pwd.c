#include "../minishell.h"

void	get_pwd(int fd)
{
	char	cwd[PATH_MAX];
	char	check_cwd[PATH_MAX];
	t_env	*env;
	t_env	*path;

	env = g_all_data->env_list;
	path = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			path = env;
			break ;
		}
		env = env->next;
	}
	if (getcwd(check_cwd, sizeof(check_cwd)) != NULL)
	{
		getcwd(cwd, sizeof(cwd));
		ft_dprintf(fd, "%s\n", cwd);
	}
	else if (path)
		ft_dprintf(fd, "%s\n", path->value);
}

void	ft_update_path(t_env **env, char *old_wd, char *new_wd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_wd);
		}
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_wd);
		}
		tmp = tmp->next;
	}
}

char	*concat_path(t_commands *commands, int size)
{
	char	*path;
	char	*tmp;
	int		i;

	path = NULL;
	i = 1;
	while (commands && commands->options[i])
	{
		tmp = path;
		path = ft_strjoin(path, commands->options[i]);
		free(tmp);
		if (i < size - 1)
		{
			tmp = path;
			path = ft_strjoin(tmp, " ");
			free(tmp);
		}
		i++;
	}
	return (path);
}

char	*ft_join_path(t_commands *commands, int size)
{
	char	*path;
	t_env	*home;
	int		i;

	i = 1;
	path = NULL;
	if (size == 1)
	{
		home = check_key("HOME");
		if (!home)
		{
			ft_dprintf(2, "%s HOME not set\n", commands->options[0]);
			return (NULL);
		}
		path = ft_strdup(home->value);
	}
	else
		path = concat_path(commands, size);
	return (path);
}

void	ft_cd(t_commands *commands)
{
	int		size;
	t_env	*env;
	char	*path;
	char	cwd[PATH_MAX];
	char	new_cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	ft_bzero(new_cwd, PATH_MAX);
	size = ft_strlen_double(commands->options);
	if (size > 2 && ft_check_slash(commands->options[size - 1]) == 0)
	{
		ft_dprintf(2, "%s: Too many arguments\n", commands->options[0]);
		return ;
	}
	path = ft_join_path(commands, size);
	env = g_all_data->env_list;
	getcwd(cwd, sizeof(cwd));
	if (path && path[0] != '\0' && chdir(path) == -1)
		ft_dprintf(2, "No such file or directory\n");
	else
	{
		getcwd(new_cwd, sizeof(new_cwd));
		ft_update_path(&env, cwd, new_cwd);
	}
	free(path);
}
