/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 21:32:53 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/09/13 16:18:13 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_u(unsigned int nb, unsigned int *byte_count)
{
	if (nb > 9)
	{
		ft_putnbr_u(nb / 10, byte_count);
		nb = nb % 10;
	}
	nb += 48;
	*byte_count += write(1, &nb, 1);
}
