/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_encrementation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:40:26 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/04 04:18:23 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *next_run(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->root;
	while (cmd)
	{
		// printf("loop");
		if(cmd->type == _EXEC) // add others type if necessary
		{
			printf("\n0");
			return (cmd);
		}	
		shell->current_pipe = (t_pipe *)cmd;
		if((shell->current_pipe->left == NULL || shell->current_pipe->left->type == _EXEC  ) && shell->current_pipe->right->type == _EXEC)
		{
			// printf("\n1");
			if( shell->current_pipe->left != NULL && shell->current_pipe->left->type == _EXEC)
				return (shell->current_pipe->left);
			else if(shell->current_pipe->right->type == _EXEC)
				return (shell->current_pipe->right);
		}
		shell->prev_pipe = (t_pipe *)cmd;
		shell->current_pipe = (t_pipe *)shell->current_pipe->left;
		if((shell->current_pipe->left == NULL || shell->current_pipe->left->type == _EXEC  ) && shell->current_pipe->right->type == _EXEC)
		{				
			// printf("\n2");
			if(shell->current_pipe->left != NULL && shell->current_pipe->left->type == _EXEC )
				return (shell->current_pipe->left);
			else if(shell->current_pipe->right->type == _EXEC)
				return (shell->current_pipe->right);
		}
		else
		{
			// printf("\n3");
			cmd = ((t_pipe *)cmd)->left;
		}
	}
	return (NULL);
}
