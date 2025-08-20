/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:07:46 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:20:12 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putnbr_u(int fd, unsigned int n)
{
	char	*base;
	int		length;

	base = "0123456789";
	length = 0;
	if (n >= 10)
		length += ft_putnbr_u(fd, (n / 10));
	length += ft_putchar(fd, base[(n % 10)]);
	return (length);
}
