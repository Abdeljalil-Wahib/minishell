#include "../minishell.h"

void	ft_generate_key_value(char *buffer, int i, char *key)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(key, "_") != 0)
	{
		if (buffer[i] && buffer[i] == '+' && buffer[i + 1] == '=')
		{
			i += 2;
			value = get_value(buffer, i);
			ft_concat_var(key, value);
		}
		else if (buffer[i] && buffer[i] == '=' && buffer[i + 1] == '\0')
			ft_add_key(key);
		else if (!buffer[i])
			ft_add_key2(key);
		else if (buffer[i])
		{
			value = get_value(buffer, (i + 1));
			ft_add_env_var(key, value);
		}
	}
	free(key);
	free(value);
}

char	*v_extract(char *buffer, char *num, char *sp_chars, int *i)
{
	char	*key;

	key = NULL;
	if (!buffer || buffer[0] == '\0')
	{
		ft_dprintf(2, "\"\": not a valid identifier\n");
		return (NULL);
	}
	else if (buffer[*i] && ft_strchr(num, buffer[*i]))
		ft_dprintf(2, "%s: not a valid identifier\n", buffer);
	while (buffer[*i] && buffer[*i] != '+' && buffer[*i] != '=')
	{
		if (ft_strchr(sp_chars, buffer[*i]))
		{
			ft_dprintf(2, "%s: not a valid identifier\n", buffer);
			free(key);
			return (NULL);
		}
		else
			key = ft_joiner(key, buffer[*i]);
		(*i)++;
	}
	return (key);
}

void	get_key(char *buffer)
{
	int		i;
	char	*key;
	char	*sp_chars;
	char	*numbers;

	i = 0;
	key = NULL;
	sp_chars = "@!\"#$%&'()*+,-.:<=>`{}|~";
	numbers = "0123456789";
	key = v_extract(buffer, numbers, sp_chars, &i);
	if (!key)
	{
		ft_dprintf(2, "%s: not a valid identifier\n", buffer);
		free(key);
		return ;
	}
	ft_generate_key_value(buffer, i, key);
}

int	get_segments(char *key, int *start, int *end)
{
	char	*res;

	if (key[*end] == ' ')
	{
		res = ft_substr(key, *start, *end);
		get_key(res);
		free(res);
		while (key[*end] && (key[*end] == ' ' || key[*end] == '\t'))
			(*end)++;
		*start = *end;
	}
	else if (key[*end] == '=' && key[*end + 1] != ' ')
	{
		res = ft_substr(key, *start, ft_strlen(key + *start));
		get_key(res);
		free(res);
		return (1);
	}
	return (0);
}

int	process_key_segment(char *key, int *start, int *end)
{
	while (key && key[*end])
	{
		if (key[*end] == ' ' || key[*end] == '=')
		{
			if (get_segments(key, start, end) == 1)
				return (1);
		}
		(*end)++;
	}
	return (0);
}
