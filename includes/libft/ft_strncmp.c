/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:10:54 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/08/02 15:24:36 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, const char *s2, int n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n < 0)
		return (-1);
	while (n > 0 && *str1 == *str2 && *str1 != '\0' && *str2 != '\0')
	{
		str1++;
		str2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*str1 - *str2);
}

