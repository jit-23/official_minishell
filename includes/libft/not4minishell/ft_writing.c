/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:29:25 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/04/03 03:43:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_writing(char *str, unsigned int *byte_count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		*byte_count += (write(1, "(null)", 6));
		return ;
	}
	while (str[i] != '\0')
	{
		*byte_count += write(1, &str[i], 1);
		i++;
	}
}
