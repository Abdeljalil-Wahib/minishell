/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 02:27:38 by mouzerzo          #+#    #+#             */
/*   Updated: 2024/08/18 04:34:03 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_checkset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	if (!s1 || !set)
		return (NULL);
	if (!s1[0])
		return (free(s1), ft_strdup(""));
	start = 0;
	while (s1[start] && ft_checkset(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && end > start && ft_checkset(set, s1[end]))
		end--;
	if (start > end)
		new_str = ft_substr(s1, 0, 0);
	else
		new_str = ft_substr(s1, start, (end - start + 1));
	free(s1);
	return (new_str);
}
