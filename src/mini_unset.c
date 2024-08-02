/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:42:37 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/31 21:42:44 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_unset(char **a, t_shell *shell)
{
	t_env	*env;
	t_env	*tmp;

	env = shell->ev;
	if(!a[1])
		return (SUCCESS);
	if(strncmp(a[1], env->env_value, str_len(env->env_value)) == 0)
	{
		shell->ev = (env->next) ? env->next : shell->ev;
		delete_node(shell, env);
		return (SUCCESS);
	}
	while (env)
	{
		if(strncmp(a[1], env->env_value, str_len(env->env_value)) == 0)
		{
			delete_node(shell, env);
			return (SUCCESS);
		}
		env = env->next;
	}	
	return (SUCCESS);
}