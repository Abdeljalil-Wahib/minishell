#include "../minishell.h"

void	ft_replace_files(t_tokens **tokens, char *file_name, int flag)
{
	t_tokens	*tmp;
	t_tokens	*new_node;

	tmp = (*tokens)->next;
	if (flag == 0)
	{
		free((*tokens)->content);
		(*tokens)->content = ft_strdup("");
	}
	else
	{
		new_node = ft_lstnew(ft_strdup(" "), t_space, t_nquoted);
		(*tokens)->next = new_node;
		(*tokens) = (*tokens)->next;
	}
	new_node = ft_lstnew(ft_strdup(file_name), t_string, t_nquoted);
	(*tokens)->next = new_node;
	(*tokens)->next->next = tmp;
}

int	ft_check_help(int i, char *tmp_file, char **cards, char *word)
{
	if (i == 0 && word[0] != '*')
	{
		if (ft_strncmp(tmp_file, cards[i], ft_strlen(cards[i])) != 0)
			return (0);
		tmp_file = tmp_file + ft_strlen(cards[i]);
	}
	else if (i == ft_strlen_double(cards) - 1)
	{
		if (word[ft_strlen(word) - 1] != '*')
		{
			if (ft_strcmp(tmp_file + (ft_strlen(tmp_file)
						- ft_strlen(cards[i])), cards[i]) != 0)
				return (0);
		}
	}
	else
	{
		tmp_file = ft_strnstr(tmp_file, cards[i], ft_strlen(tmp_file));
		if (!tmp_file)
			return (0);
	}
	return (1);
}
