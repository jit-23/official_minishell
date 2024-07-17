/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:42:37 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/17 18:42:20 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	mini_unset(char **a, t_shell *shell) // unfinished 
{
	t_env	*env;
	int i;

	i = 1;
	env = shell->ev;
	while (a[i])
	{
		if (ft_strcmp(a[i], "PATH") == 0)
		{
			write(1, "minishell: unset: PATH: cannot unset\n", 38);
			return (1);
		}
		env_remove(env, a[i]); //TO DO
		i++;
	}
	return (0);
}