/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:43:08 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:42:41 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int mini_pwd(void)
{
	char *cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	else
	{
		write(1, "Error: could not get current working directory\n", 47);
		return (ERROR);
	}
	return (SUCCESS);
}