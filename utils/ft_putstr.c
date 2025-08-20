/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:26:46 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:19:40 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putstr(int fd, char *str)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i])
	{
		ft_putchar(fd, str[i]);
		i++;
		length++;
	}
	return (length);
}
