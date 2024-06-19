/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:29:03 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/11/14 19:56:02 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_putnbr(int nb, unsigned int *byte_count)
{
	if (nb == -2147483648)
	{
		*byte_count += write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		*byte_count += write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_printf_putnbr(nb / 10, byte_count);
		nb = nb % 10;
	}
	nb += 48;
	*byte_count += write(1, &nb, 1);
}
