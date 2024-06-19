/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:25:19 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/05/02 23:25:20 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = lst;
	if (!lst)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
