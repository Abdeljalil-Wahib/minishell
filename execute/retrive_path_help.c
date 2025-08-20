#include "../minishell.h"

void	ft_free_all(t_commands *commands, char **env)
{
	ft_free(env);
	free_commands(&commands);
	ft_lstclear_env(&g_all_data->env_list);
	free(g_all_data);
}

char	*ft_check_cmd_helper(t_commands *commands, char *cmd, char **env)
{
	struct stat	sb;

	stat(cmd, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_dprintf(2, "%s: Is a directory\n", cmd);
		ft_free_all(commands, env);
		exit(126);
	}
	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(2, "%s: No such file or directory\n", cmd);
		ft_free_all(commands, env);
		exit(127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_dprintf(2, "%s: Permission denied\n", cmd);
		ft_free_all(commands, env);
		exit(127);
	}
	else
		return (cmd);
}

int	is_executable(const char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) != 0)
	{
		return (0);
	}
	if ((file_stat.st_mode & S_IFREG) && (file_stat.st_mode & S_IXUSR))
	{
		return (1);
	}
	return (0);
}
