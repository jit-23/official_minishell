/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:37:43 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/15 06:53:45 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"

int	lst_size_env(t_env *head)
{
	t_env	*node;
	int		size;

	if (!head)
		return (0);
	node = head;
	size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

int	lst_size_tokens(t_token *head)
{
	t_token	*node;
	int		size;

	if (!head)
		return (0);
	node = head;
	size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	delete_env_lst(t_env *head, int size)
{
	t_env	*del;
	int		i;

	i = -1;
	del = (head);
	while (del)
	{
		del = del->next;
		free(head->env_name);
		free(head->env_value);
		free(head);
		(head) = del;
	}
}

void	delete_token_lst(t_token *head, int size)
{
	t_token *del;
	int		i;

	i = -1;
	del = (head);
	while (++i < size)
	{
		del = del->next;
		if (head->token)
			free(head->token);
		if (head)
		{
			free(head);
			(head) = del;
		}
	}
}

void delete_2d_array(char **a)
{
	int i;

	i  = 0;
	if (!a)
		return ;
	while(a[i])
		free(a[i++]);
	free(a);
}
