/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:11:42 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:42:27 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int nbr_args(char **args)
{
	int i;

	i = 0;
	while(NULL != args[i])
		i++;
	return (i);
}

int mini_echo(t_exec *echo_cmd)
{
	char **args;
	int i;
	bool flag;
	
	flag = false;
	args = echo_cmd->args;
	i = 0;
	if(nbr_args(args) > 1)
	{
		while(args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			flag = true;
			i++;
		}
		while (args[i])
			write(1, args[i], ft_strlen(args[i]));
	}
	if (!flag)
		write(1, "\n", 1);
	return (SUCCESS);
}