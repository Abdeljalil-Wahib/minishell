/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:48:00 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:23:19 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putaddr(int fd, size_t nbr)
{
	char	*base;
	int		length;

	length = 0;
	if (!nbr)
		return (length += ft_putstr(fd, "(nil)"));
	base = "0123456789abcdef";
	if (nbr < 16)
		length += ft_putchar(fd, base[nbr]);
	if (nbr >= 16)
	{
		length += ft_putaddr(fd, nbr / 16);
		length += ft_putchar(fd, base[nbr % 16]);
	}
	return (length);
}
