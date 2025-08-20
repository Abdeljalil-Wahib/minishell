#include "../minishell.h"

int	ft_check_name(char *file, char *word)
{
	int		i;
	char	*tmp_file;
	char	**cards;

	i = 0;
	cards = NULL;
	cards = ft_split(word, '*');
	tmp_file = file;
	while (cards && cards[i])
	{
		if (ft_check_help(i, tmp_file, cards, word) == 0)
			break ;
		i++;
	}
	if (i < ft_strlen_double(cards))
	{
		ft_free(cards);
		return (0);
	}
	ft_free(cards);
	return (1);
}

void	ft_dir_by_dir(t_tokens **token, char *word)
{
	DIR				*d;
	struct dirent	*dir;
	int				flag;

	flag = 0;
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] != '.')
			{
				if (ft_check_name(dir->d_name, word) == 1)
				{
					ft_replace_files(token, dir->d_name, flag);
					(*token) = (*token)->next;
					flag++;
				}
			}
			dir = readdir(d);
		}
		closedir(d);
	}
}

void	ft_take_dir(t_tokens **token)
{
	int		flag;
	char	*word;

	flag = 0;
	word = ft_strdup((*token)->content);
	ft_dir_by_dir(token, word);
	free(word);
}

void	ft_check_wildcard(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->content && tmp->type == t_string && tmp->s_type == t_nquoted)
		{
			if (ft_strchr(tmp->content, '*') != NULL)
				ft_take_dir(&tmp);
		}
		tmp = tmp->next;
	}
}
