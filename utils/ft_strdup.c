/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:09:16 by awahib            #+#    #+#             */
/*   Updated: 2024/08/07 16:03:35 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		src_len;
	char	*dest;

	i = 0;
	src_len = ft_strlen(src);
	dest = malloc(sizeof(char) * (src_len + 1));
	if (!dest)
		return (0);
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
