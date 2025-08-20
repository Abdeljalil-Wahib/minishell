#include "../minishell.h"

void	ft_chnage_name(t_files **files, int i)
{
	t_files	*tmp_files;
	char	*name;
	char	*tmp;
	char	*index;

	tmp_files = *files;
	while (tmp_files)
	{
		if (tmp_files->type == t_heredoc)
		{
			index = ft_itoa(i);
			name = ft_strjoin("/tmp/heredoc_", index);
			tmp = ft_strjoin(name, "_");
			free(name);
			tmp_files->name = ft_strjoin(tmp, ttyname(0) + 9);
			free(tmp);
			free(index);
		}
		tmp_files = tmp_files->next;
	}
}

char	*ft_expend_herdoc(char *line)
{
	char	*line_expended;
	t_env	*env_list;
	char	*tmp;

	env_list = g_all_data->env_list;
	line_expended = ft_expand(line, env_list);
	tmp = line_expended;
	line_expended = ft_strjoin(tmp, "\n");
	free(tmp);
	return (line_expended);
}

void	ft_herdoc_helper(t_files *all_files)
{
	int		fd;
	char	*line;
	char	*line_expended;

	while (all_files)
	{
		if (all_files->type == t_heredoc)
		{
			fd = open(all_files->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
			line = readline("> ");
			while (line && ft_strcmp(all_files->limiter, line) != 0)
			{
				line_expended = ft_expend_herdoc(line);
				write(fd, line_expended, ft_strlen(line_expended));
				free(line);
				free(line_expended);
				line = readline("> ");
			}
			free(line);
			close(fd);
		}
		all_files = all_files->next;
	}
}

void	ft_run_herdoc(t_commands *commands)
{
	t_files	*all_files;

	while (commands)
	{
		all_files = commands->files;
		ft_herdoc_helper(all_files);
		commands = commands->next;
	}
}

void	ft_handel_herdoc(t_commands *commands)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		rl_clear_history();
		ft_run_herdoc(commands);
		free_commands(&commands);
		ft_lstclear_env(&g_all_data->env_list);
		free(g_all_data);
		exit(0);
	}
	else
	{
		status = 0;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_all_data->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_all_data->status = WTERMSIG(status) + 128;
	}
}
