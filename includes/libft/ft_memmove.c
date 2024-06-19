/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:10:47 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 19:09:15 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		while (n-- > 0)
		{
			str2[n] = str1[n];
		}
	}
	else
	{
		while (i < n)
		{
			str2[i] = str1[i];
			i++;
		}
	}
	return (str2);
}
