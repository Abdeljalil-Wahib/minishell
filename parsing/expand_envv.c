#include "../minishell.h"

char	*get_env_value(char *keyword, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(keyword, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*get_the_value(char *token, int *i, t_env *env)
{
	char	*value;
	char	*key;
	char	*special_chars;

	value = NULL;
	key = NULL;
	special_chars = " !/\"#$%&'()*+,-.:<=>`{}|~";
	if (token[*i] && token[*i] == '$' && token[*i + 1])
	{
		(*i)++;
		while (token[*i] && !ft_strchr(special_chars, token[*i]))
		{
			key = ft_joiner(key, token[*i]);
			(*i)++;
		}
		value = get_env_value(key, env);
		free(key);
	}
	return (value);
}

char	*ft_replace(char *token, int *i, t_env *env)
{
	char	*value;
	char	*special_chars;

	special_chars = " !/\"#$%&'()*+,-.:<=>`{}|~0123456789";
	value = NULL;
	if (token[*i] && token[*i] == '$' && token[*i + 1] && token[*i + 1] == '?')
	{
		value = ft_itoa(g_all_data->status);
		(*i) += 2;
	}
	else if (token[*i] && token[*i] == '$' && token[*i + 1]
		&& ft_strchr(special_chars, token[*i + 1]))
		(*i) += 2;
	else if (token[*i] && token[*i] == '$' && token[*i + 1]
		&& ft_strchr(special_chars, token[*i + 1]))
	{
		if (token[*i + 1] == '$')
			(*i)++;
		value = ft_joiner(value, token[*i]);
		(*i)++;
	}
	else
		ft_norm_help(&value, token, i, env);
	return (value);
}

char	*ft_expand(char *token, t_env *env)
{
	int		i;
	char	*new_token;
	char	*value;
	char	*final_str;

	i = 0;
	final_str = NULL;
	value = NULL;
	new_token = NULL;
	while (token && token[i])
	{
		new_token = ft_skip(token, &i);
		if (new_token)
			concat_values(&final_str, new_token);
		value = ft_replace(token, &i, env);
		if (value)
			concat_values(&final_str, value);
	}
	return (final_str);
}

void	expand_env(t_tokens **tokens, t_env *env)
{
	t_tokens	*tmp;
	t_tokens	*old_prev;

	tmp = *tokens;
	old_prev = tmp;
	while (tmp)
	{
		if (tmp->type == t_string)
		{
			if (old_prev->type == t_heredoc)
			{
				while (tmp && tmp->type == t_string)
				{
					if (tmp->type != t_space)
						old_prev = tmp;
					tmp = tmp->next;
				}
			}
			if (!tmp)
				return ;
			ft_help_exp(tmp, old_prev, env);
		}
		ft_help_exp_2(&tmp, &old_prev);
	}
}
