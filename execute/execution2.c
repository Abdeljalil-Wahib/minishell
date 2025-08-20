#include "../minishell.h"

int	ft_cmd_size(t_commands *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		i++;
		commands = commands->next;
	}
	return (i);
}

void	ft_serve_builtin(t_commands *commands, int fd)
{
	if (ft_strcmp(commands->options[0], "cd") == 0)
		ft_cd(commands);
	else if (ft_strcmp(commands->options[0], "env") == 0)
		print_env(fd);
	else if (ft_strcmp(commands->options[0], "pwd") == 0)
		get_pwd(fd);
	else if (ft_strcmp(commands->options[0], "export") == 0)
		ft_export(commands);
	else if (ft_strcmp(commands->options[0], "exit") == 0)
		ft_exit(commands);
	else if (ft_strcmp(commands->options[0], "unset") == 0)
		ft_unset(commands);
	else if (ft_strcmp(commands->options[0], "echo") == 0)
		ft_echo(commands, fd);
}

void	ft_dup_help(t_fds_controle *fds)
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
}

void	ft_proc_help(t_commands *commands, int *pids, char **env,
		t_fds_controle *fds)
{
	char	*cmd_path;

	pids[0] = fork();
	if (pids[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		free(pids);
		rl_clear_history();
		if (fds->write_on == -1 || fds->read_from == -1)
		{
			ft_free_all(commands, env);
			free(fds);
			exit(1);
		}
		ft_dup_help(fds);
		cmd_path = ft_check_path(commands, commands->options[0], env);
		execve(cmd_path, commands->options, env);
		ft_free(env);
		ft_lstclear_env(&g_all_data->env_list);
		free(g_all_data);
		free_commands(&commands);
		exit(1);
	}
}

void	ft_one_cmd(t_commands *commands, int *pids, char **env)
{
	t_fds_controle	*fds;

	fds = ft_handel_fds(commands->files);
	if (commands->options && commands->options[0])
	{
		if (ft_check_builtin(commands->options[0]))
		{
			if (fds->write_on == -1 || fds->read_from == -1)
				g_all_data->status = 1;
			else
				ft_serve_builtin(commands, fds->write_on);
		}
		else
		{
			ft_proc_help(commands, pids, env, fds);
			ft_wait_proc(pids, 1);
		}
	}
	free(fds);
}
