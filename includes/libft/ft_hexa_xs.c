/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_xs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:43:49 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/09/13 16:16:23 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

static void	printf_xs(unsigned int nb, char type)
{
	if (nb >= 16)
	{
		printf_xs(nb / 16, type);
		printf_xs(nb % 16, type);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + 48);
		else
		{
			if (type == 'a')
				ft_putchar(nb - 10 + 'a');
			else if (type == 'A')
				ft_putchar(nb - 10 + 'A');
		}
	}
}

void	ft_hexa_xs(unsigned int nb, char type, unsigned int *byte_count)
{
	if (nb == 0)
	{
		*byte_count += write(1, "0", 1);
		return ;
	}
	printf_xs(nb, type);
	*byte_count += ft_len(nb);
}
