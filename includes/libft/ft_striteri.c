/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:25:22 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/05/01 16:25:23 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	j;

	j = ft_strlen(s);
	i = 0;
	if (!s || !f)
		return ;
	while (i < j)
	{
		f(i, &s[i]);
		i++;
	}
}

// void    f(unsigned int i , char *str)
// {
//     if (str[i] >= 65 && str[i] <= 90)
//         str[i] += 32; 
// }

// int main()
// {
//     //int i = 0;
//     char string[] = "FERNANDO";
//     ft_striteri(string, f);
//     printf("%s",string);
//     return (0);
// }