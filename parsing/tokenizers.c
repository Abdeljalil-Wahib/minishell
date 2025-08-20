#include "../minishell.h"

void	ft_handle_str(char *str, int *i, t_tokens **tokens)
{
	char		*token;
	t_tokens	*node;

	token = NULL;
	while (str[*i] && !(str[*i] >= 9 && str[*i] <= 13) && str[*i] != 32
		&& str[*i] != 60 && str[*i] != 62 && str[*i] != 124 && str[*i] != 34
		&& str[*i] != 39)
	{
		token = ft_joiner(token, str[*i]);
		(*i)++;
	}
	node = ft_lstnew(token, t_string, t_nquoted);
	ft_lstadd_back(tokens, node);
}

void	ft_handle_red(char *str, int *i, t_tokens **tokens)
{
	char		*token;
	t_tokens	*node;
	char		target;

	token = 0;
	target = str[*i];
	while (str[*i] && str[*i] == target)
	{
		token = ft_joiner(token, str[*i]);
		(*i)++;
	}
	if (ft_strlen(token) == 2 && target == '>')
		node = ft_lstnew(token, t_append, t_nquoted);
	else if (ft_strlen(token) == 2 && target == '<')
		node = ft_lstnew(token, t_heredoc, t_nquoted);
	else if (ft_strlen(token) == 1 && target == '>')
		node = ft_lstnew(token, t_outred, t_nquoted);
	else if (ft_strlen(token) == 1 && target == '<')
		node = ft_lstnew(token, t_inred, t_nquoted);
	else
		node = ft_lstnew(token, t_rerror, t_nquoted);
	ft_lstadd_back(tokens, node);
}

void	ft_handle_pipe(char *str, int *i, t_tokens **tokens)
{
	char		*token;
	t_tokens	*node;

	token = 0;
	while (str[*i] && str[*i] == 124)
	{
		token = ft_joiner(token, str[*i]);
		(*i)++;
		if (str[*i] && str[*i] == 124)
			break ;
	}
	node = ft_lstnew(token, t_pipe, t_nquoted);
	ft_lstadd_back(tokens, node);
}

void	ft_handle_quotes(char *str, int *i, t_tokens **tokens)
{
	char		*token;
	t_tokens	*node;
	char		target;
	int			flag;

	token = NULL;
	flag = 0;
	target = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != target)
	{
		token = ft_joiner(token, str[*i]);
		(*i)++;
		flag = 1;
	}
	if (flag == 0)
		token = ft_strdup("");
	(*i)++;
	if (target == 39)
		node = ft_lstnew(token, t_string, t_squoted);
	else
		node = ft_lstnew(token, t_string, t_dquoted);
	ft_lstadd_back(tokens, node);
}

void	ft_tokeniser(char *str, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_handle_quotes(str, &i, tokens);
		else if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 60
			&& str[i] != 62 && str[i] != 124)
			ft_handle_str(str, &i, tokens);
		else if (str[i] == 60 || str[i] == 62)
			ft_handle_red(str, &i, tokens);
		else if (str[i] == 124)
			ft_handle_pipe(str, &i, tokens);
		else if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)
			|| str[i] == '\n')
			ft_handle_space(str, &i, tokens);
	}
}
