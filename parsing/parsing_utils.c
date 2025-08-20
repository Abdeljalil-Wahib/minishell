#include "../minishell.h"

void	add_files(char *file_name, t_toktype type, t_strtype s_type,
		t_commands *currentNode)
{
	t_files	*new_file;

	new_file = NULL;
	if (type == t_heredoc)
		new_file = ft_lstnew_files(NULL, file_name, type, s_type);
	if (type == t_inred)
		new_file = ft_lstnew_files(file_name, NULL, type, s_type);
	ft_lstadd_back_files(&currentNode->files, new_file);
}

void	concat_values(char **final_str, char *str)
{
	char	*tmp;

	tmp = *final_str;
	*final_str = ft_strjoin(*final_str, str);
	free(tmp);
	free(str);
	str = NULL;
}

void	ft_norm_help(char **value, char *token, int *i, t_env *env)
{
	if (token[*i] && token[*i] == '$' && !token[*i + 1])
	{
		*value = ft_joiner(*value, token[*i]);
		(*i)++;
	}
	else
		*value = get_the_value(token, i, env);
}

char	*ft_skip(char *token, int *i)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (token[*i] && token[*i] != '$')
	{
		tmp_str = ft_joiner(tmp_str, token[*i]);
		(*i)++;
	}
	return (tmp_str);
}
