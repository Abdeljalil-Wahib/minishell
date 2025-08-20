#include "../minishell.h"

char	*ft_joiner(char *str, char c)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

void	ft_handle_space(char *str, int *i, t_tokens **tokens)
{
	char		*token;
	t_tokens	*node;

	token = 0;
	while (str[*i] && (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13)
			|| str[*i] == '\n'))
	{
		token = ft_joiner(token, str[*i]);
		(*i)++;
	}
	node = ft_lstnew(token, t_space, t_nquoted);
	ft_lstadd_back(tokens, node);
}
