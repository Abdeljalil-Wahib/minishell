#include "../minishell.h"

void	ft_start_proc_help(int *pids)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	rl_clear_history();
	free(pids);
}

int	ft_pipe_fork(int *pipe_fd)
{
	int	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	return (pid);
}
