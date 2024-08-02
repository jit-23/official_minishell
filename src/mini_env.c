/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:58:46 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:40:44 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_env(t_shell *shell)
{
	char **env;
	char *tmp;
	int i;

	i = -1;
	env = shell->env;
	while (env[++i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	return (SUCCESS);
}