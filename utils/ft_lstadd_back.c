/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:05:13 by awahib            #+#    #+#             */
/*   Updated: 2024/08/08 12:57:28 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}

void	ft_lstadd_back_command(t_commands **lst, t_commands *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast_command(*lst)->next = new;
		else
			*lst = new;
	}
}

void	ft_lstadd_back_files(t_files **lst, t_files *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast_file(*lst)->next = new;
		else
			*lst = new;
	}
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast_env(*lst)->next = new;
		else
			*lst = new;
	}
}
