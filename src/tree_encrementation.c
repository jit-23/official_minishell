/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_encrementation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescalei <eescalei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:40:26 by eescalei          #+#    #+#             */
/*   Updated: 2024/08/02 19:07:33 by eescalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *next_run(t_shell *shell)
{
	t_cmd *cmd;
	t_pipe *pip1;
	t_pipe *pip2;

	cmd = shell->root;
	pip1 = NULL;
	pip2 = NULL;
	while (cmd)
	{
		if(cmd->type == _PIPE)
		{
			pip1 = ((t_pipe *)cmd);
			if(pip1->left != NULL)
			{
				if(pip1->left->type == _EXEC)
				{
					set_pipe_fds(shell, pip1, NULL, LEFT);
				}	
				else if(((t_pipe *)(pip1->left))->left->type == _EXEC)
				{
					pip2 = (t_pipe *)(pip1->left);
					set_pipe_fds(shell, pip1, pip2, LEFT);
				}
					cmd = (t_cmd *)pip1->left;
			}
			else if(pip1->right != NULL)
			{
				cmd = (t_cmd *)pip1->right;
				if(pip1->right->type ==  _EXEC)
					set_pipe_fds(shell, NULL, NULL, RIGHT); // cmd on the right miss pipe managment
			}
		}
		if(cmd->type == _REDIR)
			return(cmd);
		if(cmd->type == _EXEC)
			return(cmd);
	}
	return (cmd);
}
