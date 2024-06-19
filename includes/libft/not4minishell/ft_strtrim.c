/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:07:09 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/10/14 15:37:01 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= j)
		i++;
	if (i > j)
		return (ft_strdup((s1 + j + 1)));
	while (ft_strchr(set, s1[j]) && j >= 0)
		j--;
	str = (char *)malloc(sizeof(char) * (j - i) + 2);
	if (!str)
		return (0);
	ft_memcpy(str, &s1[i], (j - i) + 2);
	str[(j - i) + 1] = '\0';
	return (str);
}
/* int main()
{
	char name[] = "fernando";
	char const n[] = "fo";
	printf("%s", ft_strtrim(name, n));	
} */