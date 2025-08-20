/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouzerzo <mouzerzo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:05:55 by awahib            #+#    #+#             */
/*   Updated: 2024/08/18 23:57:52 by mouzerzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_lstnew(char *content, t_toktype type, t_strtype s_type)
{
	t_tokens	*node;

	node = ft_calloc(sizeof(t_tokens), 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->s_type = s_type;
	node->next = NULL;
	node->expanded = 0;
	return (node);
}

t_files	*ft_lstnew_files(char *name, char *limiter, t_toktype type,
		t_strtype s_type)
{
	t_files	*node;

	node = ft_calloc(sizeof(t_files), 1);
	if (!node)
		return (NULL);
	node->name = name;
	node->limiter = limiter;
	node->type = type;
	node->s_type = s_type;
	node->next = NULL;
	return (node);
}

t_commands	*ft_lstnew_commands(void)
{
	t_commands	*node;

	node = ft_calloc(sizeof(t_commands), 1);
	if (!node)
		return (NULL);
	return (node);
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}
