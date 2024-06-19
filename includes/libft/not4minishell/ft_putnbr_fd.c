/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:01:56 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/11/14 19:57:02 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		nb = 147483648;
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr((nb / 10), fd);
		nb = nb % 10;
	}
	nb += 48;
	write(fd, &nb, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}

//  int main()
//  {
//     int fd;
//     fd = open("somefile.txt", O_RDWR);
// 	ft_putnbr_fd(745, fd);
//     close(fd); 
//     return (0);
//  }
