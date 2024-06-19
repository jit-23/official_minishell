/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:05:21 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/03/31 02:21:02 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	char			*str;
	unsigned char	chr;

	chr = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != chr)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (&str[i]);
}



