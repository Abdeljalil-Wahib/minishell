#include "../minishell.h"

void	ft_fcmd_dup(int *pipe_fd, t_fds_controle *fds)
{
	if (fds->write_on == 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
		{
			perror("");
			exit(1);
		}
	}
	else
	{
		if (dup2(fds->write_on, 1) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->write_on);
	}
	free(fds);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	ft_mcmd_dup(int *pipe_fd, t_fds_controle *fds)
{
	if (fds->write_on != 1)
	{
		if (dup2(fds->write_on, 1) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->write_on);
	}
	else
	{
		if (dup2(pipe_fd[1], 1) == -1)
		{
			perror("");
			exit(1);
		}
	}
	free(fds);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	ft_lcmd_dup(int *pipe_fd, t_fds_controle *fds)
{
	if (fds->read_from != 0)
	{
		if (dup2(fds->read_from, 0) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->read_from);
	}
	if (fds->write_on != 1)
	{
		if (dup2(fds->write_on, 1) == -1)
		{
			perror("");
			exit(1);
		}
		close(fds->write_on);
	}
	free(fds);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
