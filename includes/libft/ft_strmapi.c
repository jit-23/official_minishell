/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 23:00:47 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/04/26 18:56:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char my_func(unsigned int i, char str)
// {
// 	printf("My inner function: index = %d and %c\n", i, str);
// 	return str - 32;
// }
// int main()
// {
// 	char str[10] = "hello.";
// 	printf("The result is %s\n", str);
// 	char *result = ft_strmapi(str, my_func);
// 	printf("The result is %s\n", result);
// 	return 0;
// }