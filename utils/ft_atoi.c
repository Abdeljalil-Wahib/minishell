/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:44:07 by awahib            #+#    #+#             */
/*   Updated: 2024/08/08 13:44:19 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	convert(const char *str, long long number, size_t i)
{
	while (str[i] >= 48 && str[i] <= 57)
	{
		number *= 10;
		number += str[i] - 48;
		i++;
	}
	return (number);
}

long long	ft_atoi(const char *str)
{
	size_t		i;
	int			msign;
	long long	number;

	i = 0;
	msign = 1;
	number = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			msign *= -1;
		i++;
	}
	number = convert(str, number, i);
	return (number * msign);
}
