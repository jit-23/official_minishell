/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:26:23 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/23 02:56:35 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	mini_export(char **args, t_env *ev, t_env *hiden) // unfinished
{
	int	new_ev;
	int	status;

	new_ev = 0;
	if(!args[1])
	{
		print_env(hiden);
		return (SUCCESS);
	}
	else
	{
		status = check_env(args[1]);
		if (args[1][0] == '=' )
			status = -3;
		if(status <= 0)
			return (print_error(status, args[1]));
		new_ev = status == 2 ? 1 : is_in_env(ev, args[1]);
		if(new_ev == 0)
		{
			if(status == 1)
				add_env(args[1], ev);
			add_env(args[1], hiden);
		}
	}
	return (SUCCESS);
}