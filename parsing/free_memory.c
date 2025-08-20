#include "../minishell.h"

void	free_files(t_files *files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->name);
		free(tmp->limiter);
		free(tmp);
	}
}

void	free_commands(t_commands **commands)
{
	t_commands	*tmp;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		ft_free(tmp->options);
		free_files(tmp->files);
		free(tmp);
	}
}
