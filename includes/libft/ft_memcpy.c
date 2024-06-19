/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:18 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 19:05:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	i = 0;
	if (!str2 && !str1)
		return (0);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}
