/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:59:14 by awahib            #+#    #+#             */
/*   Updated: 2024/08/15 18:49:07 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_countwords(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

int	ft_skip_sep(char const *str, char sep, int start)
{
	while (str[start] && str[start] == sep)
		start++;
	return (start);
}

char	**ft_wordcpy(char **strs, char *str, char sep)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	end = 0;
	while (str && str[start])
	{
		start = ft_skip_sep(str, sep, start);
		end = start;
		while (str[end] && str[end] != sep)
			end++;
		strs[i] = ft_substr(str, start, (end - start));
		if (!strs[i])
			return (ft_free(strs), NULL);
		i++;
		start = end;
		start = ft_skip_sep(str, sep, start);
	}
	return ((strs[i] = NULL), strs);
}

char	**ft_split(char *str, char sep)
{
	char	**strs;

	if (!str)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_countwords(str, sep) + 1));
	if (!strs)
		return (NULL);
	if (!ft_countwords(str, sep))
		return ((strs[0] = NULL), strs);
	strs = ft_wordcpy(strs, str, sep);
	return (strs);
}
