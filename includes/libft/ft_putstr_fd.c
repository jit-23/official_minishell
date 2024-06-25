/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:31:09 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/25 04:01:52 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

//  int main()
//  {
//      int i = 0;
//      char string[] = "there is a tring here";
//      int fd;
//      fd = open("somefile.txt", O_RDWR);
//		ft_putstr_fd(string, fd);
//      close(fd); 
//      return (0);
//  }
