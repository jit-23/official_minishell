/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:53:52 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 18:17:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;
	char	*needle;

	hay = (char *)big;
	needle = (char *)little;
	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0 || hay == little)
		return (hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (hay[i + j] == needle[j] && needle[j] && i + j < len)
		{
			j++;
		}
		if (needle[j] == '\0')
			return (&hay[i]);
		i++;
	}
	return (NULL);
}
