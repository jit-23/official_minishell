/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:31:09 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/05/01 18:31:13 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
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
