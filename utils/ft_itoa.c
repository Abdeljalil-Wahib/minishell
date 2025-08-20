/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:50:00 by mouzerzo          #+#    #+#             */
/*   Updated: 2024/08/08 12:56:57 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_intostr(char *str, long n, int len)
{
	int	i;

	i = 0;
	str[len] = '\0';
	len--;
	if (n < 0)
	{
		n *= -1;
		str[i] = '-';
		i++;
	}
	while (len >= i)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	number;

	number = n;
	len = ft_numlen(number);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str = ft_intostr(str, number, len);
	return (str);
}
