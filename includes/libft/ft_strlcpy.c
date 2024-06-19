/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:12:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 19:15:45 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*sorc;

	sorc = (char *)src;
	i = 0;
	if (size == 0)
		return (ft_strlen(sorc));
	while (sorc[i] && i < (size - 1))
	{
		dst[i] = sorc[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(sorc));
}
