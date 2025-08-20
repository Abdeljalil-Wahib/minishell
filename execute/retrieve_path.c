#include "../minishell.h"

char	**ft_get_path(char **env)
{
	int		i;
	char	**key_value;
	char	*path;
	char	**paths;

	i = 0;
	paths = NULL;
	path = NULL;
	while (env && env[i])
	{
		key_value = ft_split(env[i], '=');
		if (ft_strcmp(key_value[0], "PATH") == 0)
			break ;
		ft_free(key_value);
		key_value = NULL;
		i++;
	}
	if (key_value)
		path = ft_strdup(key_value[1]);
	ft_free(key_value);
	if (path)
		paths = ft_split(path, ':');
	free(path);
	return (paths);
}

int	ft_cmd_exec_check(char *cmd)
{
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) != -1)
		return (1);
	return (0);
}

char	*ft_get_cmdpath(char **paths, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	cmd_path = NULL;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (is_executable(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

char	*ft_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;

	if (cmd && !cmd[0])
		return (NULL);
	paths = ft_get_path(env);
	cmd_path = ft_get_cmdpath(paths, cmd);
	if (!paths || !paths[0])
	{
		if (access(cmd, X_OK) != -1)
			return (cmd);
	}
	ft_free(paths);
	return (cmd_path);
}

char	*ft_check_path(t_commands *commands, char *cmd, char **env)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_strchr(cmd, '/'))
		cmd_path = ft_check_cmd_helper(commands, cmd, env);
	else
		cmd_path = ft_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_dprintf(2, "%s: command not found\n", cmd);
		ft_free_all(commands, env);
		exit(127);
	}
	return (cmd_path);
}
