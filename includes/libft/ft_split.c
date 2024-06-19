/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 23:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/01/12 23:26:04 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_string(char const *str, char c, int i)
{
	int	size;

	size = 0;
	while (str[i] != c && str[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**strings;
	int		size;

	i = 0;
	j = 0;
	count = ft_count(s, c);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	while (i < count)
	{
		while (s[j] == c)
			j++;
		size = size_string(s, c, j);
		strings[i] = ft_substr(s, j, size);
		j += size;
		i++;
	}
	strings[i] = 0;
	return (strings);
}
