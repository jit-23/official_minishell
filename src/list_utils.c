/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:18:06 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/07/20 10:34:46 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_node(t_shell *mini, t_env *env)
{
	if(mini->ev == env && env->next == NULL)
	{
		if(mini->ev->prev)
			mini->ev->prev->next = NULL;
		free(env->env_value);
		free(mini->ev->env_name);
		return ;
	}
	if(env->prev)
		env->prev->next = env->next;
	if(env->next)
		env->next->prev = env->prev;
	free(env->env_name);
	free(env);
}

t_token *new_node(char *token, t_type type, t_placing placing) // prev e definido na funcao na qual este e chamada
{
    t_token *new_node;
	
    new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token = token;
	new_node->type = type;
    new_node->placing = placing;
    new_node->next = NULL;
    return (new_node);
}

void	delete_lst(t_token **head, int size)
{
	t_token	*del;

	auto int i = -1;
 	del = (*head);
	while (++i < size)
	{
		del = del->next;
		free(*head);
		(*head) = del;
	}
}

t_token	*ft_lstlast(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int	lst_size(t_token **head)
{
	t_token	*node;
	int		size;

	if (!(*head))
		return (0);
	node = (*head);
	size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	add_to_list(t_lexer *token_list, char *word, t_type type, t_placing placing)
{
	t_token *head;
	t_token *prev;
	t_token *last;

	if (!token_list->head)
	{
		token_list->head = new_node(word, type, placing);
		token_list->head->prev = NULL;
		token_list->official_head = token_list->head;
		return ;
	}
	last = ft_lstlast(token_list->head);
	last->next = new_node(word, type, placing);
	prev = last;
	last = last->next;
	last->prev = prev;
}