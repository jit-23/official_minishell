/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:44:08 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/09/13 16:16:34 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *string, ...)
{
	unsigned int	i;
	unsigned int	byte_count;
	va_list			args;

	i = 0;
	byte_count = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			ft_check_specifier(string, (i + 1), args, &byte_count);
			i += 2;
		}
		else
		{
			byte_count += write(1, &string[i], 1);
			i++;
		}
	}
	va_end(args);
	return (byte_count);
}
