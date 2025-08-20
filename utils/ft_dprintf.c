/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:40:20 by awahib            #+#    #+#             */
/*   Updated: 2024/08/15 19:05:53 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		length;
	int		i;

	va_start(ap, format);
	length = 0;
	i = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i] == '\0')
				return (-1);
			length += ft_print_format(fd, format[i], ap);
		}
		else
			length += ft_putchar(fd, format[i]);
		i++;
	}
	return (length);
}
