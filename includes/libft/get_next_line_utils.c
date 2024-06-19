/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:45:26 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/11/14 19:55:42 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_gnl_strjoin(char *start, char *buff)
{
	char	*ptr;

	if (!start)
	{
		start = (char *)malloc(1 * sizeof(char));
		start[0] = '\0';
	}
	if (!buff)
		return (NULL);
	ptr = (char *)malloc(1 + ft_strlen(start) + ft_strlen(buff) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_join(ptr, start, buff);
	free(start);
	return (ptr);
}

char	*ft_join(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
