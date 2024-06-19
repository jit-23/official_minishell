/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:07:57 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/14 18:48:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* clear linked list for the env vars. */
#include "../includes/minishell.h"

void delete_all(t_shell *shell)
{
	delete_token_lst(shell->token_list->head, lst_size_tokens(shell->token_list->head));
	free(shell->token_list);
	//delete_env_lst(shell->ev, lst_size_env(shell->ev));
	//free(shell->prompt);
}

/* delete tokens that contain the env vars and its value */

/* void delete_exec(t_exec * 
\'exec->args)1;
} */
/* 
void delete_tree(t_cmd *root)
{
	static int j;
    t_exec *ex;
    t_redir *redir;
    t_pipe *pp;
    if (root == NULL)
        return ;
    if (root->type == _EXEC)
    {
        ex = (t_exec *)root;
		delete_exec();
    }
	else if (root->type == _REDIR)
	{
		redir = (t_redir *)root;
		delete_tree((t_cmd *)redir->cmd);
	}
    else if (root->type == _PIPE)
    {
        pp = (t_pipe *)root;

        delete_tree((t_cmd *)pp->left);
        delete_tree((t_cmd *)pp->right);
    }
}
 */