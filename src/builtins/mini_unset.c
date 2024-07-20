/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:42:37 by eescalei          #+#    #+#             */
/*   Updated: 2024/07/20 10:46:03 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_unset(char **a, t_shell *shell) // unfinished 
{
	t_env	*env;
	t_env	*tmp;

	env = shell->ev;
	if(!a[1])
		return (0);
	if(strncmp(a[1], env->value, str_len(env->value)) == 0)
	{
		shell->ev = (env->next) ? env->next : shell->ev;
		delete_node(shell, env);
		return (0);
	}
	while (env)
	{
		if(strncmp(a[1], env->value, str_len(env->value)) == 0)
		{
			delete_node(shell, env);
			return (0);
		}
		env = env->next;
	}	
	return (0);
}