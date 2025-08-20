/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:45:47 by mouzerzo          #+#    #+#             */
/*   Updated: 2024/08/10 14:48:21 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	size_t	j;

	if (!haystack && !needle)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && needle_len <= len - i)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j])
			j++;
		if (needle_len == j)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
