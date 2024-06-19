/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:56:44 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/10 20:57:07 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str1;
	char	*str2;
	char	*ptr;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	ptr = (char *) malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + 2));
	if (!ptr)
		return (0);
	ft_memcpy(ptr, str1, ft_strlen(str1));
	ptr[ft_strlen(str1)] = 's';
	while (str2[i])
	{
		ptr[ft_strlen(str1) + i] = str2[i];
		i++;
	}
	ptr[ft_strlen(str1) + i] = '\0';
	return (ptr);
}
