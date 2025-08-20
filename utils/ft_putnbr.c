/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:20 by awahib            #+#    #+#             */
/*   Updated: 2024/08/11 22:17:58 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putnbr(int fd, int n)
{
	long int	nbr;
	int			length;

	nbr = n;
	length = 0;
	if (nbr < 0)
	{
		ft_putchar(fd, '-');
		nbr = nbr * -1;
		length++;
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar(fd, nbr + '0');
		length++;
	}
	if (nbr >= 10)
	{
		length += ft_putnbr(fd, (nbr / 10));
		length += ft_putnbr(fd, (nbr % 10));
	}
	return (length);
}
