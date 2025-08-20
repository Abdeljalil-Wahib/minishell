/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awahib <awahib@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:04:12 by awahib            #+#    #+#             */
/*   Updated: 2024/07/31 20:03:26 by awahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_tokens **lst)
{
	t_tokens	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp->content);
			free(tmp);
		}
	}
}

void	ft_lstclear_env(t_env **env)
{
	t_env	*tmp;

	if (env)
	{
		while (*env)
		{
			tmp = *env;
			*env = (*env)->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
	}
}
