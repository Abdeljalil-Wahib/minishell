#include "../minishell.h"

void	process_command(t_tokens **tmptok, t_commands *currentNode)
{
	int		is_unquoted;
	char	*command;
	char	*tmp;

	while (*tmptok && (*tmptok)->type == t_string)
	{
		is_unquoted = 0;
		command = NULL;
		while (*tmptok && (*tmptok)->type == t_string)
		{
			if ((*tmptok)->s_type == t_nquoted && (*tmptok)->expanded)
				is_unquoted = 1;
			tmp = command;
			command = ft_strjoin(tmp, (*tmptok)->content);
			free(tmp);
			*tmptok = (*tmptok)->next;
		}
		currentNode->options = args_inserter(currentNode->options, command,
				is_unquoted);
		free(command);
		if (*tmptok && (*tmptok)->next && (*tmptok)->next->type == t_space)
			*tmptok = (*tmptok)->next;
	}
	if (*tmptok && (*tmptok)->type == t_space)
		*tmptok = (*tmptok)->next;
}

void	process_append_outred(t_tokens **tmptok, t_commands *c_Node, char *tmp)
{
	t_toktype	type;
	t_strtype	s_type;
	char		*file_name;
	t_files		*new_file;

	if (*tmptok && ((*tmptok)->type == t_append || (*tmptok)->type == t_outred))
	{
		type = (*tmptok)->type;
		s_type = t_nquoted;
		*tmptok = (*tmptok)->next;
		if (*tmptok && (*tmptok)->type == t_space)
			*tmptok = (*tmptok)->next;
		file_name = NULL;
		while (*tmptok && (*tmptok)->type == t_string)
		{
			if ((*tmptok)->s_type != t_nquoted)
				s_type = (*tmptok)->s_type;
			tmp = file_name;
			file_name = ft_strjoin(file_name, (*tmptok)->content);
			free(tmp);
			*tmptok = (*tmptok)->next;
		}
		new_file = ft_lstnew_files(file_name, NULL, type, s_type);
		ft_lstadd_back_files(&c_Node->files, new_file);
	}
}

void	process_inred_heredoc(t_tokens **tmptok, t_commands *currentNode)
{
	t_toktype	type;
	t_strtype	s_type;
	char		*file_name;
	char		*tmp;

	if (*tmptok && ((*tmptok)->type == t_inred || (*tmptok)->type == t_heredoc))
	{
		type = (*tmptok)->type;
		s_type = t_nquoted;
		*tmptok = (*tmptok)->next;
		if (*tmptok && (*tmptok)->type == t_space)
			*tmptok = (*tmptok)->next;
		file_name = NULL;
		while (*tmptok && (*tmptok)->type == t_string)
		{
			if ((*tmptok)->s_type != t_nquoted)
				s_type = (*tmptok)->s_type;
			tmp = file_name;
			file_name = ft_strjoin(file_name, (*tmptok)->content);
			free(tmp);
			*tmptok = (*tmptok)->next;
		}
		add_files(file_name, type, s_type, currentNode);
	}
}

void	generate_execution_input(t_tokens *tokens, t_commands **commands)
{
	t_tokens	*tmptok;
	t_commands	*current_node;
	char		*tmp;

	tmptok = tokens;
	while (tmptok)
	{
		current_node = ft_lstnew_commands();
		ft_lstadd_back_command(commands, current_node);
		while (tmptok && tmptok->type != t_pipe)
		{
			tmp = NULL;
			process_command(&tmptok, current_node);
			process_append_outred(&tmptok, current_node, tmp);
			process_inred_heredoc(&tmptok, current_node);
		}
		if (tmptok)
			tmptok = tmptok->next;
	}
	return ;
}

int	parsing(t_tokens **tokens, t_commands **commands, char *line, t_env *env)
{
	if (check_syntax(line))
		ft_tokeniser(line, tokens);
	else
		return (0);
	if (!check_syntax2(*tokens))
	{
		ft_dprintf(2, "Syntax error\n");
		return (0);
	}
	expand_env(tokens, env);
	ft_check_wildcard(tokens);
	generate_execution_input(*tokens, commands);
	ft_lstclear(tokens);
	return (1);
}
