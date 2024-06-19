/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:18:06 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/13 16:58:03 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *new_node(char *token, t_type type, t_placing placing) // prev e definido na funcao na qual este e chamada
{
    t_token *new_node;
	
    new_node = (t_token *)ft_calloc(6 ,sizeof(t_token));
	//printf("\t token - %s\n",token);
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
	//printf("ADD_TO_LIST :\n");
	//printf("word - %s\n",word);
	//printf("type - %d\n",type);
	//printf("placing - %u\n",placing);
	if (!token_list->head)
	{
		
		token_list->head = new_node(word, type, placing);
		token_list->head->prev = NULL;
		return ;
	}
	last = ft_lstlast(token_list->head);
	last->next = new_node(word, type, placing);
	//printf("last->next->token - %s\n",last->next->token);
	prev = last;
	last = last->next;
	last->prev = prev;
}

/* 
void	fill_stack(long *nbrs, t_stack **head, int size)
{
	int		i;
	t_stack	*prev;
	t_stack	*a;

	i = 0;
	a = (*head);
	prev = (*head);
	while (i < size)
	{
		if (i == 0)
		{
			a->x = nbrs[i];
			a->prev = NULL;
		}
		else
		{
			a->next = ft_lstnew(nbrs[i]);
			a = a->next;
			a->prev = prev;
			prev = prev->next;
		}
		i++;
	}
	a->next = NULL;
} */