/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_chrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:21:10 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/03/31 02:51:12 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_find_chrs(char *main_str, char *c_to_look)
{
	size_t			i;
	size_t			j;
	
	i = 0;
	j = 0;
	while(c_to_look[i])
	{
		j = 0;
		while(main_str[j])
		{
			if (c_to_look[i] == main_str[j])
				return (&main_str[j]);
			j++;
		}
		i++;
	}
	return (NULL);
}
