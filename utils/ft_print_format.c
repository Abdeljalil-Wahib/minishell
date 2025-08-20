/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:52:20 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:21:57 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_format(int fd, const char format, va_list ap)
{
	int		length;
	size_t	address;

	length = 0;
	if (format == 'd' || format == 'i')
		length = ft_putnbr(fd, va_arg(ap, int));
	else if (format == 'X' || format == 'x')
		length = ft_puthex(fd, va_arg(ap, unsigned int), format);
	else if (format == 'c')
		length = ft_putchar(fd, va_arg(ap, int));
	else if (format == 's')
		length = ft_putstr(fd, va_arg(ap, char *));
	else if (format == 'u')
		length = ft_putnbr_u(fd, va_arg(ap, unsigned int));
	else if (format == '%')
		length = ft_putchar(fd, '%');
	else if (format == 'p')
	{
		address = va_arg(ap, size_t);
		if (address != 0)
			length += ft_putstr(fd, "0x") + ft_putaddr(fd, address);
		else
			length += ft_putaddr(fd, address);
	}
	return (length);
}
