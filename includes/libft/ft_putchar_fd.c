/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:07:36 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/05/01 17:07:37 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <fcntl.h>
// int main()
// {
//     int i = 0;
//     char string[] = "there is a tring here";
//     int fd;
//     fd = open("somefile.txt", O_WRONLY);
//     while(string[i])
//     {
//         ft_putchar_fd(string[i], fd);
//         i++;
//     }
//     close(fd); 
//     return (0);
// }
