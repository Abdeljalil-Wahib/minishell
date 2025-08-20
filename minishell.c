#include "minishell.h"

t_execute	*g_all_data;

void	ft_name_herdoc(t_commands **commands)
{
	int			i;
	t_commands	*tmp;

	i = 0;
	tmp = *commands;
	while (tmp)
	{
		ft_chnage_name(&tmp->files, i);
		tmp = tmp->next;
		i++;
	}
}

int	ft_mini_help(t_commands **commands, t_tokens **tokens, char *line)
{
	if (parsing(tokens, commands, line, g_all_data->env_list) == 0)
		return (0);
	free(line);
	if (*commands)
	{
		ft_name_herdoc(commands);
		ft_execute(commands);
	}
	return (1);
}

void	minishell(t_tokens **tokens, int x)
{
	t_commands	*commands;
	char		*line;

	commands = NULL;
	dup2(x, 0);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell $> ");
	line = ft_strtrim(line, " \t");
	signal(SIGINT, SIG_IGN);
	if (!line)
	{
		rl_clear_history();
		ft_lstclear_env(&g_all_data->env_list);
		free(g_all_data);
		exit(1);
	}
	if (*line)
	{
		add_history(line);
	}
	if (ft_mini_help(&commands, tokens, line) == 0)
		return ;
	free_commands(&commands);
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*tokens;
	t_env		*our_env;
	int			x;

	(void)ac;
	(void)av;
	tokens = NULL;
	our_env = NULL;
	signal(SIGQUIT, handle_sig);
	get_env(env, &our_env);
	g_all_data = malloc(sizeof(t_execute));
	g_all_data->status = 0;
	g_all_data->env_list = our_env;
	x = dup(0);
	while (1)
	{
		minishell(&tokens, x);
		ft_lstclear(&tokens);
	}
}
