/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:40:35 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:21:39 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_convert(int fd, unsigned int nbr, char *base, char format)
{
	int	length;

	length = 0;
	if (nbr < 16)
		length += ft_putchar(fd, base[nbr]);
	if (nbr >= 16)
	{
		length += ft_puthex(fd, nbr / 16, format);
		length += ft_puthex(fd, nbr % 16, format);
	}
	return (length);
}

int	ft_puthex(int fd, unsigned int nbr, char format)
{
	char	*base;
	int		length;

	length = 0;
	if (format == 'X')
	{
		base = "0123456789ABCDEF";
		length += ft_convert(fd, nbr, base, format);
	}
	else if (format == 'x')
	{
		base = "0123456789abcdef";
		length += ft_convert(fd, nbr, base, format);
	}
	return (length);
}
