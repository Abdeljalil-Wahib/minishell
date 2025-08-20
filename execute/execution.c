#include "../minishell.h"

void	ft_parent_help(int *pipe_fd, t_commands **commands, int *i)
{
	if (dup2(pipe_fd[0], 0) == -1)
	{
		perror("");
		exit(1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	(*commands) = (*commands)->next;
	(*i)++;
}

void	ft_start_procs(int size, t_commands *commands, int *pids, char **env)
{
	int			i;
	int			pipe_fd[2];
	t_commands	*tmp;

	i = 0;
	tmp = commands;
	while (i < size && commands)
	{
		pids[i] = ft_pipe_fork(pipe_fd);
		if (pids[i] == -1)
			return ;
		else if (pids[i] == 0)
		{
			ft_start_proc_help(pids);
			if (i == 0)
				ft_first_cmd(tmp, commands, pipe_fd, env);
			else if (i == size - 1)
				ft_last_cmd(tmp, commands, pipe_fd, env);
			else
				ft_mid_cmd(tmp, commands, pipe_fd, env);
		}
		else
			ft_parent_help(pipe_fd, &commands, &i);
	}
}

void	ft_wait_proc(int *pids, int size)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < size)
	{
		waitpid(pids[i], &exit_status, 0);
		i++;
	}
	if (WIFEXITED(exit_status))
		g_all_data->status = WEXITSTATUS(exit_status);
	if (WIFSIGNALED(exit_status))
		g_all_data->status = WTERMSIG(exit_status) + 128;
}

void	ft_handel_proc(t_commands *commands)
{
	int		size;
	int		*pids;
	char	**env;

	size = ft_cmd_size(commands);
	pids = malloc(sizeof(pid_t) * size);
	env = ft_convert_env(g_all_data->env_list);
	if (!pids)
		return ;
	if (size == 1)
		ft_one_cmd(commands, pids, env);
	else
	{
		ft_start_procs(size, commands, pids, env);
		ft_wait_proc(pids, size);
	}
	ft_free(env);
	free(pids);
}

void	ft_execute(t_commands **commands)
{
	t_files	*all_files;

	ft_handel_herdoc(*commands);
	if (g_all_data->status != 130)
		ft_handel_proc(*commands);
	all_files = (*commands)->files;
	while (all_files)
	{
		if (all_files->type == t_heredoc)
			unlink(all_files->name);
		all_files = all_files->next;
	}
}
