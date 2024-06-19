/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:38:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/25 22:59:25 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*src1;
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	src1 = (char *)src;
	len_s = ft_strlen(src1);
	len_d = ft_strlen(dst);
	if (dstsize <= len_d)
		return (dstsize + len_s);
	i = 0;
	while (src1[i] != '\0' && len_d + 1 < dstsize)
	{
		dst[len_d] = src1[i];
		len_d++;
		i++;
	}
	dst[len_d] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src1[i]));
}
