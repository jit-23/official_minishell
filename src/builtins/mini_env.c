/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:58:46 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/17 18:54:17 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_shell *shell)
{
	t_env *env;

	env = shell->ev;
	while (env)
	{
		write(1, env->name, ft_strlen(env->name));
		write(1, "=", 1);
		write(1, env->value , ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}