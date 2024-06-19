/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:28:40 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/10/17 01:25:46 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_specifier(const char *str, int i, va_list args,
	unsigned int *byte_count)
{
	if (str[i] == '%')
		*byte_count += ft_putchar('%');
	else if (str[i] == 'c')
		*byte_count += ft_putchar(va_arg(args, int));
	else if (str[i] == 's')
		ft_writing(va_arg(args, char *), byte_count);
	else if (str[i] == 'u')
		ft_putnbr_u(va_arg(args, unsigned int), byte_count);
	else if (str[i] == 'd' || str[i] == 'i')
		ft_printf_putnbr(va_arg(args, int), byte_count);
	else if (str[i] == 'x')
		ft_hexa_xs(va_arg(args, unsigned int), 'a', byte_count);
	else if (str[i] == 'X')
		ft_hexa_xs(va_arg(args, unsigned int), 'A', byte_count);
	else if (str[i] == 'p')
		ft_hexa_p(va_arg(args, unsigned long long), byte_count);
	else
		*byte_count += ft_putchar('0');
}
