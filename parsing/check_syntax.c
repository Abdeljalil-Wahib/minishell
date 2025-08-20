#include "../minishell.h"

int	check_syntax(char *str)
{
	int		i;
	char	target;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			target = str[i++];
			while (str && str[i] && str[i] != target)
				i++;
			if (!str[i] || str[i] != target)
			{
				ft_dprintf(2, "Syntax error\n");
				return (0);
			}
		}
		if (str[i])
			i++;
	}
	return (1);
}

int	check_lastnode(t_tokens *tokens)
{
	t_tokens	*last_node;

	last_node = ft_lstlast(tokens);
	if (last_node->type != t_string && last_node->type != t_space)
		return (0);
	return (1);
}

int	check_redirections(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == t_inred || tokens->type == t_outred
			|| tokens->type == t_append || tokens->type == t_heredoc)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == t_space)
				tokens = tokens->next;
			if ((tokens && tokens->type != t_string) || !tokens)
				return (0);
		}
		else if (tokens->type == t_rerror)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	check_pipe(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == t_pipe)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == t_space)
				tokens = tokens->next;
			if ((tokens && tokens->type == t_pipe) || !tokens)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	check_syntax2(t_tokens *tokens)
{
	if (tokens && (!check_lastnode(tokens) || tokens->type == t_pipe))
		return (0);
	else if (tokens && (!check_redirections(tokens) || !check_pipe(tokens)))
		return (0);
	return (1);
}
