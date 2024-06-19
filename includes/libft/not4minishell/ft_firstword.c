/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_firstword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:39:03 by fde-jesu          #+#    #+#             */
/*   Updated: 2023/12/24 02:46:46 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*alloc_wrd(char *command, char *wrd, int start, int end)
{
	int	i;

	i = 0;
	wrd = (char *)malloc(sizeof(char *) * (end - start) + 1);
	if (!wrd)
	{
		write(1, "error on \"wrd\" allocation\n", 26);
		exit(1);
	}
	while (i < (end - start))
	{
		wrd[i] = command[start + i];
		i++;
	}
	wrd[i] = '\0';
	return (wrd);
}

char	*ft_firstword(char *command)
{
	int		i;
	int		j;
	char	*wrd;

	wrd = NULL;
	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			i++;
		j = i;
		while (command[j] != ' ')
		{
			j++;
			if (!(command[j] != ' '))
				break ;
		}
		break ;
	}
	return (alloc_wrd(command, wrd, i, j));
}
