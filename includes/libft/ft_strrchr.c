/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:36:25 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 18:12:55 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*ptr;
	unsigned char	chr;

	chr = (unsigned char)c;
	ptr = (char *)s;
	i = ft_strlen(ptr);
	while (i >= 0)
	{
		if (ptr[i] == chr)
			return (&ptr[i]);
		i--;
	}
	return (0);
}
