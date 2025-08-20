/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:25:14 by awahib            #+#    #+#             */
/*   Updated: 2024/08/08 13:01:28 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	t_len;

	i = 0;
	j = 0;
	t_len = ft_strlen(s1) + ft_strlen(s2);
	newstr = malloc(sizeof(char) * (t_len + 1));
	if (!newstr)
		return (NULL);
	while (s1 && s1[i])
		newstr[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		newstr[j++] = s2[i++];
	return ((newstr[j] = '\0'), newstr);
}
