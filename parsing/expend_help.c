#include "../minishell.h"

void	ft_help_exp(t_tokens *tmp, t_tokens *old_prev, t_env *env)
{
	char	*tmp_content;

	if (tmp->s_type != t_squoted && old_prev->type != t_heredoc)
	{
		if (tmp->content && ft_strchr(tmp->content, '$') != NULL)
		{
			tmp_content = tmp->content;
			tmp->content = ft_expand(tmp->content, env);
			tmp->expanded = 1;
			free(tmp_content);
		}
	}
}

void	ft_help_exp_2(t_tokens **tmp, t_tokens **old_prev)
{
	if ((*tmp)->type != t_space)
		(*old_prev) = (*tmp);
	(*tmp) = (*tmp)->next;
}
