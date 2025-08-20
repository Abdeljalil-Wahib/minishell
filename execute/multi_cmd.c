#include "../minishell.h"

void	ft_exec_handel(t_commands *tmp, t_commands *commands, char **env)
{
	char	*cmd_path;

	if (ft_check_builtin(commands->options[0]))
	{
		ft_serve_builtin(commands, 1);
		exit(0);
	}
	cmd_path = ft_check_path(tmp, commands->options[0], env);
	execve(cmd_path, commands->options, env);
	free(cmd_path);
	ft_free_all(commands, env);
	exit(1);
}

void	ft_first_cmd(t_commands *tmp, t_commands *commands, int *pipe_fd,
		char **env)
{
	t_fds_controle	*fds;

	fds = ft_handel_fds(commands->files);
	if (fds->read_from == -1 || fds->write_on == -1)
	{
		free(fds);
		ft_free_all(tmp, env);
		exit(1);
	}
	if (fds->read_from != 0)
	{
		if (dup2(fds->read_from, 0) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->read_from);
	}
	ft_fcmd_dup(pipe_fd, fds);
	if (!commands->options || !commands->options[0])
	{
		ft_free_all(tmp, env);
		exit(0);
	}
	ft_exec_handel(tmp, commands, env);
}

void	ft_mid_cmd(t_commands *tmp, t_commands *commands, int *pipe_fd,
		char **env)
{
	t_fds_controle	*fds;

	fds = ft_handel_fds(commands->files);
	if (fds->read_from == -1 || fds->write_on == -1)
	{
		free(fds);
		ft_free_all(tmp, env);
		exit(1);
	}
	if (fds->read_from != 0)
	{
		if (dup2(fds->read_from, 0) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->read_from);
	}
	ft_mcmd_dup(pipe_fd, fds);
	if (!commands->options || !commands->options[0])
	{
		ft_free_all(tmp, env);
		exit(0);
	}
	ft_exec_handel(tmp, commands, env);
}

void	ft_last_cmd(t_commands *tmp, t_commands *commands, int *pipe_fd,
		char **env)
{
	t_fds_controle	*fds;

	fds = ft_handel_fds(commands->files);
	if (fds->read_from == -1 || fds->write_on == -1)
	{
		free(fds);
		ft_free_all(tmp, env);
		exit(1);
	}
	ft_lcmd_dup(pipe_fd, fds);
	if (!commands->options || !commands->options[0])
	{
		ft_free_all(tmp, env);
		exit(0);
	}
	ft_exec_handel(tmp, commands, env);
}
